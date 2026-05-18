#include "PresetSettingsDialog.h"
#include "../../Theme/Theme.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QFrame>

static QFrame *MakeSeparator(QWidget *parent) {
    auto *frame = new QFrame(parent);
    frame->setFrameShape(QFrame::HLine);
    frame->setStyleSheet(QString("color: %1;").arg(Theme::BORDER_DARK));
    return frame;
}

static QLabel *MakeSectionLabel(const QString &text, QWidget *parent) {
    auto *label = new QLabel(text, parent);
    label->setStyleSheet(Theme::SettingsDialogSectionLabelStyle());
    return label;
}

PresetSettingsDialog::PresetSettingsDialog(const StoreSettings &settings,
                                           bool editable,
                                           QWidget *parent)
    : QDialog(parent)
    , m_isPreset(settings.isPreset)
{
    BuildUI(settings, editable);
}

PresetSettingsDialog *PresetSettingsDialog::CreateNew(QWidget *parent) {
    StoreSettings blank;
    blank.name           = "Новий пресет";
    blank.isPreset       = false;
    blank.textileParams  = ReportParams{.minCount = 1, .maxCount = 6, .lowCount = 3};
    blank.footwearParams = ReportParams{.minCount = 1, .maxCount = 1, .lowCount = 3};
    blank.textileReports  = TextileReportFlags{true, false, true, true, true};
    blank.footwearReports = FootwearReportFlags{true, true, false};

    return new PresetSettingsDialog(blank, true, parent);
}

StoreSettings PresetSettingsDialog::GetSettings() const {
    StoreSettings settings;
    settings.name      = m_nameEdit->text().trimmed().toStdString();
    settings.isPreset  = false;

    settings.textileParams = ReportParams{
        .minCount = m_textileMinCount->value(),
        .maxCount = m_textileMaxCount->value(),
        .lowCount = m_textileLowCount->value()
    };
    settings.footwearParams = ReportParams{
        .minCount = m_footwearMinCount->value(),
        .maxCount = m_footwearMaxCount->value(),
        .lowCount = m_footwearLowCount->value()
    };
    settings.textileReports = TextileReportFlags{
        .addSizes           = m_textileAddSizes->isChecked(),
        .addAndReplaceSizes = m_textileAddAndReplaceSizes->isChecked(),
        .addProducts        = m_textileAddProducts->isChecked(),
        .lowCountStore      = m_textileLowCountStore->isChecked(),
        .lowCountHall       = m_textileLowCountHall->isChecked()
    };
    settings.footwearReports = FootwearReportFlags{
        .addSizes      = m_footwearAddSizes->isChecked(),
        .lowCountStore = m_footwearLowCountStore->isChecked(),
        .lowCountHall  = m_footwearLowCountHall->isChecked()
    };
    return settings;
}

void PresetSettingsDialog::BuildUI(const StoreSettings &settings, bool editable) {
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedWidth(320);
    setStyleSheet("PresetSettingsDialog { background: transparent; }");

    auto *root = new QVBoxLayout(this);
    root->setContentsMargins(0, 0, 0, 0);
    root->setSpacing(0);

    auto *card = new QFrame(this);
    card->setObjectName("card");
    card->setStyleSheet(Theme::SettingsDialogCardStyle());

    auto *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(14, 12, 14, 12);
    cardLayout->setSpacing(6);

    auto *nameRow = new QHBoxLayout();
    auto *nameLabel = new QLabel("Назва:", card);
    nameLabel->setStyleSheet(Theme::SettingsDialogNameLabelStyle());

    m_nameEdit = new QLineEdit(QString::fromStdString(settings.name), card);
    m_nameEdit->setReadOnly(!editable);
    m_nameEdit->setStyleSheet(Theme::SettingsDialogNameEditStyle(editable));

    nameRow->addWidget(nameLabel);
    nameRow->addWidget(m_nameEdit, 1);
    cardLayout->addLayout(nameRow);
    cardLayout->addWidget(MakeSeparator(card));

    auto *scrollArea = new QScrollArea(card);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setMaximumHeight(380);
    scrollArea->setStyleSheet(Theme::SettingsDialogScrollAreaStyle());

    auto *innerWidget = new QWidget(scrollArea);
    innerWidget->setStyleSheet("background: transparent;");
    scrollArea->setWidget(innerWidget);

    auto *innerLayout = new QVBoxLayout(innerWidget);
    innerLayout->setContentsMargins(0, 4, 0, 4);
    innerLayout->setSpacing(5);

    innerLayout->addWidget(MakeSectionLabel("Текстиль — параметри", innerWidget));
    m_textileMinCount = AddSpinRow(innerWidget, innerLayout, "Мінімальна кількість", settings.textileParams.minCount, 1, 999, editable);
    m_textileMaxCount = AddSpinRow(innerWidget, innerLayout, "Максимальна кількість", settings.textileParams.maxCount, 1, 999, editable);
    m_textileLowCount = AddSpinRow(innerWidget, innerLayout, "Низька кількість", settings.textileParams.lowCount, 1, 999, editable);

    innerLayout->addWidget(MakeSectionLabel("Текстиль — звіти", innerWidget));
    m_textileAddSizes = AddCheckRow(innerWidget, innerLayout,
        "Довішування розмірів", settings.textileReports.addSizes, editable);
    m_textileAddAndReplaceSizes = AddCheckRow(innerWidget, innerLayout,
        "Довішування та відвішування за сіткою (2 звіти)", settings.textileReports.addAndReplaceSizes, editable);
    m_textileAddProducts = AddCheckRow(innerWidget, innerLayout,
        "Відсутні артикули в залі", settings.textileReports.addProducts, editable);
    m_textileLowCountStore = AddCheckRow(innerWidget, innerLayout,
        "Залишки в магазині", settings.textileReports.lowCountStore, editable);
    m_textileLowCountHall = AddCheckRow(innerWidget, innerLayout,
        "Залишки в залі", settings.textileReports.lowCountHall, editable);

    innerLayout->addSpacing(4);
    innerLayout->addWidget(MakeSeparator(innerWidget));

    innerLayout->addWidget(MakeSectionLabel("Взуття — параметри", innerWidget));
    m_footwearMinCount = AddSpinRow(innerWidget, innerLayout, "Мінімальна кількість", settings.footwearParams.minCount, 1, 999, editable);
    m_footwearMaxCount = AddSpinRow(innerWidget, innerLayout, "Максимальна кількість", settings.footwearParams.maxCount, 1, 999, editable);
    m_footwearLowCount = AddSpinRow(innerWidget, innerLayout, "Низька кількість", settings.footwearParams.lowCount, 1, 999, editable);

    innerLayout->addWidget(MakeSectionLabel("Взуття — звіти", innerWidget));
    m_footwearAddSizes = AddCheckRow(innerWidget, innerLayout,
        "Довішування розмірів", settings.footwearReports.addSizes, editable);
    m_footwearLowCountStore = AddCheckRow(innerWidget, innerLayout,
        "Залишки в магазині", settings.footwearReports.lowCountStore, editable);
    m_footwearLowCountHall = AddCheckRow(innerWidget, innerLayout,
        "Залишки в залі", settings.footwearReports.lowCountHall, editable);

    innerLayout->addStretch();
    cardLayout->addWidget(scrollArea, 1);

    if (editable) {
        cardLayout->addWidget(MakeSeparator(card));

        auto *buttonRow = new QHBoxLayout();
        buttonRow->setSpacing(8);

        auto *deleteButton = new QPushButton("Видалити", card);
        deleteButton->setStyleSheet(Theme::SettingsDialogActionButtonStyle());
        connect(deleteButton, &QPushButton::clicked, this, [this]() {
            m_deleteRequested = true;
            reject();
        });

        auto *cancelButton = new QPushButton("Скасувати", card);
        cancelButton->setStyleSheet(Theme::SettingsDialogActionButtonStyle());
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

        auto *saveButton = new QPushButton("Зберегти", card);
        saveButton->setDefault(true);
        saveButton->setStyleSheet(Theme::SettingsDialogSaveButtonStyle());
        connect(saveButton, &QPushButton::clicked, this, &QDialog::accept);

        buttonRow->addWidget(deleteButton);
        buttonRow->addStretch();
        buttonRow->addWidget(cancelButton);
        buttonRow->addWidget(saveButton);
        cardLayout->addLayout(buttonRow);
    }

    root->addWidget(card);
}

QSpinBox *PresetSettingsDialog::AddSpinRow(QWidget *parent, QVBoxLayout *layout,
                                           const QString &label, int value,
                                           int min, int max, bool editable)
{
    auto *row = new QWidget(parent);
    row->setStyleSheet("background: transparent;");

    auto *rowLayout = new QHBoxLayout(row);
    rowLayout->setContentsMargins(0, 0, 0, 0);
    rowLayout->setSpacing(6);

    auto *rowLabel = new QLabel(label, row);
    rowLabel->setStyleSheet(QString("color: %1; font-size: 11px;").arg(Theme::TEXT_NORMAL));

    auto *spinBox = new QSpinBox(row);
    spinBox->setRange(min, max);
    spinBox->setValue(value);
    spinBox->setFixedWidth(60);
    spinBox->setReadOnly(!editable);
    spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    spinBox->setStyleSheet(Theme::SettingsDialogSpinBoxStyle(editable));

    rowLayout->addWidget(rowLabel);
    rowLayout->addStretch();
    rowLayout->addWidget(spinBox);
    layout->addWidget(row);
    return spinBox;
}

QCheckBox *PresetSettingsDialog::AddCheckRow(QWidget *parent, QVBoxLayout *layout, const QString &label, bool checked, bool editable)
{
    auto *checkBox = new QCheckBox(parent);
    checkBox->setChecked(checked);
    checkBox->setVisible(false);

    auto *row = new QWidget(parent);
    row->setStyleSheet("background: transparent;");

    auto *rowLayout = new QHBoxLayout(row);
    rowLayout->setContentsMargins(0, 1, 0, 1);
    rowLayout->setSpacing(7);

    auto *indicator = new QPushButton(row);
    indicator->setCheckable(true);
    indicator->setChecked(checked);
    indicator->setEnabled(editable);
    indicator->setFixedSize(14, 14);

    auto refreshIndicator = [indicator](bool isChecked) {
        indicator->setText(isChecked ? "\u25A0" : "");
        indicator->setStyleSheet(Theme::SettingsDialogCheckIndicatorStyle(isChecked));
    };
    refreshIndicator(checked);

    QObject::connect(indicator, &QPushButton::toggled, checkBox, &QCheckBox::setChecked);
    QObject::connect(indicator, &QPushButton::toggled, indicator, refreshIndicator);

    rowLayout->addWidget(indicator);

    if (editable) {
        auto *labelButton = new QPushButton(label, row);
        labelButton->setFlat(true);
        labelButton->setStyleSheet(Theme::SettingsDialogCheckLabelButtonStyle());
        connect(labelButton, &QPushButton::clicked, indicator, &QPushButton::toggle);
        rowLayout->addWidget(labelButton, 1);
    } else {
        auto *labelWidget = new QLabel(label, row);
        labelWidget->setStyleSheet(Theme::SettingsDialogCheckLabelReadOnlyStyle());
        rowLayout->addWidget(labelWidget, 1);
    }

    layout->addWidget(row);
    return checkBox;
}
