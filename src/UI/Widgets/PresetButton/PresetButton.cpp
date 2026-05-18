#include "PresetButton.h"
#include "PresetSettingsDialog.h"
#include "../../Theme/Theme.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QScreen>

PresetButton::PresetButton(QWidget *parent)
    : QWidget(parent)
{
    m_presets.push_back(MakeConceptPreset());
    m_presets.push_back(MakeDiscountPreset());

    for (auto &preset : PresetStorage::Load()) {
        m_presets.push_back(std::move(preset));
    }

    m_activeIndex = 0;

    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_mainButton = new QPushButton(this);
    m_mainButton->setMinimumHeight(32);
    m_mainButton->setStyleSheet(Theme::PresetMainButtonStyle());
    connect(m_mainButton, &QPushButton::clicked, this, &PresetButton::OnArrowClicked);

    m_arrowButton = new QPushButton("▾", this);
    m_arrowButton->setFixedSize(22, 32);
    m_arrowButton->setStyleSheet(Theme::PresetArrowButtonStyle());
    connect(m_arrowButton, &QPushButton::clicked, this, &PresetButton::OnArrowClicked);

    layout->addWidget(m_mainButton);
    layout->addWidget(m_arrowButton);

    SelectPreset(0);
}

std::vector<StoreSettings> PresetButton::GetActiveSettings() const {
    if (m_activeIndex >= 0 && m_activeIndex < (int)m_presets.size()) {
        return { m_presets[m_activeIndex] };
    }
    return {};
}

void PresetButton::SelectPreset(int index) {
    m_activeIndex = index;
    m_mainButton->setText(QString::fromStdString(m_presets[index].name));
    emit ActivePresetChanged();
}

void PresetButton::OnArrowClicked() {
    if (m_popup && m_popup->isVisible()) {
        ClosePopup();
        return;
    }
    ShowPopup();
}

void PresetButton::SavePresets() const {
    PresetStorage::Save(m_presets);
}

void PresetButton::ClosePopup() {
    if (m_popup) {
        m_popup->hide();
        m_popup->deleteLater();
        m_popup = nullptr;
    }
}

void PresetButton::ShowPopup() {
    ClosePopup();

    m_popup = new QFrame(nullptr, Qt::Popup | Qt::FramelessWindowHint);
    m_popup->setAttribute(Qt::WA_DeleteOnClose);
    m_popup->setFixedWidth(260);
    m_popup->setStyleSheet(Theme::PresetPopupFrameStyle());

    connect(m_popup, &QFrame::destroyed, this, [this]() { m_popup = nullptr; });

    auto *popupLayout = new QVBoxLayout(m_popup);
    popupLayout->setContentsMargins(4, 4, 4, 4);
    popupLayout->setSpacing(2);

    for (int i = 0; i < (int)m_presets.size(); ++i) {
        const auto &preset = m_presets[i];
        bool isActive = (i == m_activeIndex);

        auto *row = new QFrame(m_popup);
        row->setStyleSheet(Theme::PresetPopupRowStyle(isActive));

        auto *rowLayout = new QHBoxLayout(row);
        rowLayout->setContentsMargins(6, 2, 4, 2);
        rowLayout->setSpacing(4);

        auto *nameButton = new QPushButton(QString::fromStdString(preset.name), row);
        nameButton->setFlat(true);
        nameButton->setStyleSheet(Theme::PresetPopupNameButtonStyle(isActive));

        int capturedIndex = i;
        connect(nameButton, &QPushButton::clicked, this, [this, capturedIndex]() {
            SelectPreset(capturedIndex);
            ClosePopup();
        });

        rowLayout->addWidget(nameButton, 1);

        auto *dotsButton = new QPushButton("•••", row);
        dotsButton->setFixedSize(28, 24);
        dotsButton->setStyleSheet(Theme::PresetPopupDotsButtonStyle());

        bool isPreset = preset.isPreset;
        StoreSettings capturedSettings = preset;
        connect(dotsButton, &QPushButton::clicked, this, [this, capturedIndex, capturedSettings, isPreset]() {
            auto *senderButton = qobject_cast<QPushButton *>(sender());
            QPoint globalPosition = senderButton->mapToGlobal(QPoint(senderButton->width(), 0));

            auto *dialog = new PresetSettingsDialog(capturedSettings, !isPreset,
                                                    m_popup ? m_popup->parentWidget() : this);

            QRect screen = QApplication::primaryScreen()->availableGeometry();
            int x = globalPosition.x() + 4;
            int y = globalPosition.y();
            if (x + 320 > screen.right()) { x = globalPosition.x() - 320 - 4; }
            if (y + 480 > screen.bottom()) { y = screen.bottom() - 480; }
            dialog->move(x, y);

            if (!isPreset) {
                int result = dialog->exec();
                if (result == QDialog::Accepted) {
                    m_presets[capturedIndex] = dialog->GetSettings();
                    if (capturedIndex == m_activeIndex) {
                        m_mainButton->setText(QString::fromStdString(m_presets[capturedIndex].name));
                        emit ActivePresetChanged();
                    }
                    SavePresets();
                    ClosePopup();
                    ShowPopup();
                } else if (dialog->WasDeleteRequested()) {
                    m_presets.erase(m_presets.begin() + capturedIndex);
                    if (m_activeIndex >= (int)m_presets.size()) { m_activeIndex = (int)m_presets.size() - 1; }
                    if (m_activeIndex < 0) { m_activeIndex = 0; }
                    SelectPreset(m_activeIndex);
                    SavePresets();
                    ClosePopup();
                    ShowPopup();
                }
            } else {
                dialog->exec();
            }
            dialog->deleteLater();
        });

        rowLayout->addWidget(dotsButton);
        popupLayout->addWidget(row);
    }

    auto *separator = new QFrame(m_popup);
    separator->setFrameShape(QFrame::HLine);
    separator->setStyleSheet(Theme::PresetPopupSeparatorStyle());
    popupLayout->addWidget(separator);

    auto *addButton = new QPushButton("＋  Додати нові налаштування", m_popup);
    addButton->setStyleSheet(Theme::PresetPopupAddButtonStyle());
    connect(addButton, &QPushButton::clicked, this, &PresetButton::OnAddNewPreset);
    popupLayout->addWidget(addButton);

    QPoint globalPosition = mapToGlobal(QPoint(0, height()));
    QRect screen = QApplication::primaryScreen()->availableGeometry();
    int x = globalPosition.x();
    int y = globalPosition.y() + 2;
    if (x + 260 > screen.right()) { x = screen.right() - 264; }

    m_popup->move(x, y);
    m_popup->show();
    m_popup->adjustSize();
}

void PresetButton::OnAddNewPreset() {
    ClosePopup();

    auto *dialog = PresetSettingsDialog::CreateNew(this);

    QPoint globalPosition = mapToGlobal(QPoint(0, height() + 2));
    QRect screen = QApplication::primaryScreen()->availableGeometry();
    int x = globalPosition.x();
    int y = globalPosition.y();
    if (x + 320 > screen.right()) { x = screen.right() - 324; }
    if (y + 500 > screen.bottom()) { y = screen.bottom() - 504; }
    dialog->move(x, y);

    if (dialog->exec() == QDialog::Accepted) {
        m_presets.push_back(dialog->GetSettings());
        SavePresets();
        SelectPreset((int)m_presets.size() - 1);
    }
    dialog->deleteLater();
}
