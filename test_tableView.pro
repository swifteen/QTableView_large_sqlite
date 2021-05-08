HEADERS       += connection.h \
                tableModel.h \
                tableView.h
SOURCES       += tableModel.cpp\
                tableView.cpp \
                test_tableView.cpp
									
QT           += sql widgets
requires(qtConfig(tableview))

# install
target.path = $$[QT_INSTALL_EXAMPLES]/sql/tablemodel
INSTALLS += target

