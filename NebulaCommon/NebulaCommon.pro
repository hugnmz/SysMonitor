QT -= gui

TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

# Thay vì liệt kê SOURCES/HEADERS ở đây, hãy dùng file .pri
include(NebulaCommon.pri)

# Các phần cấu hình deployment giữ nguyên...
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    NebulaCommon.pri

include(NebulaCommon.pri)
