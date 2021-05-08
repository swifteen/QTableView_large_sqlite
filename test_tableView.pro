HEADERS       += connection.h \
                tableModel.h \
                tableView.h \
    form.h
SOURCES       += tableModel.cpp\
                tableView.cpp \
                test_tableView.cpp \
    form.cpp
									
QT           += sql widgets
requires(qtConfig(tableview))

# install
target.path = $$[QT_INSTALL_EXAMPLES]/sql/tablemodel
INSTALLS += target

FORMS += \
    form.ui

