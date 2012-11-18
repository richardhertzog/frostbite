#include "highlighteditdialog.h"
#include "ui_highlighteditdialog.h"

HighlightEditDialog::HighlightEditDialog(HighlightTextTab *textTab, QWidget *parent) :
        QDialog(parent), ui(new Ui::HighlightEditDialog) {

    ui->setupUi(this);

    parenDialog = (QDialog*)parent;
    settings = HighlightSettings::Instance();

    this->textTab = textTab;

    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelPressed()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(okPressed()));
}

void HighlightEditDialog::showEvent(QShowEvent * event) {
    QDialog::showEvent(event);
    this->move(parenDialog->x() + (parenDialog->height() / 4),
               parenDialog->y() + (parenDialog->width() / 4));

    ui->textLine->setFocus();

    ui->textLine->setText(entry.value);

    int index = ui->groupSelect->findText(entry.group);
    if(index != -1) {
        ui->groupSelect->setCurrentIndex(index);
    } else {
        ui->groupSelect->setCurrentIndex(0);
    }
}

QComboBox* HighlightEditDialog::getGroupSelect() {
    return ui->groupSelect;
}

void HighlightEditDialog::setEntry(HighlightSettingsEntry entry) {
    this->entry = entry;
}

void HighlightEditDialog::okPressed() {
    this->entry.group = ui->groupSelect->currentText();
    this->entry.value = ui->textLine->text();

    settings->setParameter("TextHighlight", this->entry);
    textTab->reloadHighlightList();

    this->accept();
}

void HighlightEditDialog::cancelPressed() {
    this->reject();
}

HighlightEditDialog::~HighlightEditDialog() {
    delete ui;
}