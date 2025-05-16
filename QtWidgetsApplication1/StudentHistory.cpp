#include "StudentHistory.h"
#include<queue>
#include <QTableWidget>
#include <QString>
#include <string>
#include"StudentMainMenu.h"
using namespace std;

StudentHistory::StudentHistory(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    connect(ui.BackBtn, &QPushButton::clicked, this, &StudentHistory::backbtnclicked);
}

void StudentHistory::displayStudentHistory(queue<string>historyqueue)
{
   
        // Clear old content
        ui.HistoryTable->clear();
        ui.HistoryTable->setRowCount(static_cast<int>(historyqueue.size()));
        ui.HistoryTable->setColumnCount(2);

        // Set column headers
        ui.HistoryTable->setHorizontalHeaderLabels(QStringList() << "Index" << "Action");

        // Fill rows
        int index = 0;
        while (!historyqueue.empty()) {
            QString indexStr = QString::number(index + 1);
            QString actionStr = QString::fromStdString(historyqueue.front());

            ui.HistoryTable->setItem(index, 0, new QTableWidgetItem(indexStr));
            ui.HistoryTable->setItem(index, 1, new QTableWidgetItem(actionStr));

            historyqueue.pop();
            ++index;
        }

        // Optional: Fit columns to contents
        ui.HistoryTable->resizeColumnsToContents();

        // Optional: Make table read-only
        ui.HistoryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
}
void StudentHistory::backbtnclicked()
{
    StudentMainMenu* s = new StudentMainMenu(this);
    s->show();
    this->hide();
}

StudentHistory::~StudentHistory()
{}


// Function to display the queue in the HistoryTable


