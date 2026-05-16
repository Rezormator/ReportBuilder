#include "StoreTypeDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>

#include "../../Theme/Theme.h"

StoreTypeDialog::StoreTypeDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("ReportBuilder - Вибір типу магазину");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setMinimumWidth(280);
    setModal(true);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(16);
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setAlignment(Qt::AlignHCenter);

    auto *titleLabel = new QLabel("<h2>Тип магазину</h2>", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    auto *groupBox = new QGroupBox(this);
    groupBox->setStyleSheet("QGroupBox { border: 1px solid #ccc; border-radius: 6px; padding: 12px; }");
    auto *groupLayout = new QVBoxLayout(groupBox);
    groupLayout->setSpacing(8);

    m_radioButtonConcept = new QRadioButton("Концепт", this);
    m_radioButtonConcept->setChecked(true);
    m_radioButtonConcept->setStyleSheet("font-size: 14px; font-weight: bold;");

    m_radioButtonDiscount = new QRadioButton("Дисконт", this);
    m_radioButtonDiscount->setStyleSheet("font-size: 14px; font-weight: bold;");

    groupLayout->addWidget(m_radioButtonConcept);
    groupLayout->addWidget(m_radioButtonDiscount);
    mainLayout->addWidget(groupBox);

    auto *confirmButton = new QPushButton("Підтвердити", this);
    confirmButton->setDefault(true);
    confirmButton->setMinimumSize(130, 36);
    confirmButton->setStyleSheet(Theme::StoreTypeDialogStyle());

    auto *buttonRow = new QHBoxLayout();
    buttonRow->addStretch();
    buttonRow->addWidget(confirmButton);
    buttonRow->addStretch();
    mainLayout->addLayout(buttonRow);

    connect(confirmButton, &QPushButton::clicked, this, &StoreTypeDialog::OnConfirm);
}

void StoreTypeDialog::OnConfirm() {
    m_selected = m_radioButtonConcept->isChecked() ? StoreType::Concept : StoreType::Discount;
    accept();
}
