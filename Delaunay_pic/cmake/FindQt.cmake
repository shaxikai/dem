find_package(Qt4)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
include_directories(${QT_INCLUDE_DIR})
set(QT_LIBRARIES QtGui QtCore QtXml QtOpenGL)

list(APPEND QT_LIBRARIES QtDeclarative QtSvg QtSql QtOpenGL QtGui QtNetwork QtCore GL pthread)
