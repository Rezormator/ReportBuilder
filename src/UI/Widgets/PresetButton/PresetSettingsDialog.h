#pragma once

#include <QDialog>
#include <QCheckBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QVBoxLayout>

#include "../../../Infrastructure/AppSettings.h"

class PresetSettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit PresetSettingsDialog(const StoreSettings &settings,
                                  bool editable,
                                  QWidget *parent = nullptr);

    static PresetSettingsDialog *CreateNew(QWidget *parent = nullptr);

    [[nodiscard]] StoreSettings GetSettings() const;
    [[nodiscard]] bool WasDeleteRequested() const { return m_deleteRequested; }

private:
    void BuildUI(const StoreSettings &settings, bool editable);

    QSpinBox  *AddSpinRow(QWidget *parent, QVBoxLayout *layout,
                          const QString &label, int value, int min, int max, bool editable);
    QCheckBox *AddCheckRow(QWidget *parent, QVBoxLayout *layout,
                           const QString &label, bool checked, bool editable);

    QLineEdit *m_nameEdit = nullptr;

    QSpinBox *m_textileMinCount = nullptr;
    QSpinBox *m_textileMaxCount = nullptr;
    QSpinBox *m_textileLowCount = nullptr;

    QCheckBox *m_textileAddSizes           = nullptr;
    QCheckBox *m_textileAddAndReplaceSizes = nullptr;
    QCheckBox *m_textileAddProducts        = nullptr;
    QCheckBox *m_textileLowCountStore      = nullptr;
    QCheckBox *m_textileLowCountHall       = nullptr;

    QSpinBox *m_footwearMinCount = nullptr;
    QSpinBox *m_footwearMaxCount = nullptr;
    QSpinBox *m_footwearLowCount = nullptr;

    QCheckBox *m_footwearAddSizes      = nullptr;
    QCheckBox *m_footwearLowCountStore = nullptr;
    QCheckBox *m_footwearLowCountHall  = nullptr;

    bool m_deleteRequested = false;
    bool m_isPreset        = false;
};
