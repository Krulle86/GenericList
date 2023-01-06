qt_add_library(GenericList STATIC
    genericlistmodel.h genericlistmodel.cpp
    genericitemlist.cpp genericitemlist.h
    registertypes.h
)

target_link_libraries(GenericList PRIVATE
    Qt6::Core
    Qt6::Qml
)
