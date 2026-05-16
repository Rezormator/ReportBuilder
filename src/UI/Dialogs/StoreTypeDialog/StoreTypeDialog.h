#pragma once

#include <QDialog>
#include <QRadioButton>

enum class StoreType {
    Concept,
    Discount
};

class StoreTypeDialog : public QDialog {
    Q_OBJECT

public:
    explicit StoreTypeDialog(QWidget *parent = nullptr);

    [[nodiscard]] StoreType SelectedType() const { return m_selected; }

private slots:
    void OnConfirm();

private:
    StoreType m_selected = StoreType::Concept;
    QRadioButton *m_radioButtonConcept = nullptr;
    QRadioButton *m_radioButtonDiscount = nullptr;
};
