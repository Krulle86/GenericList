# Generic Listmodel for QML

This is an example implementation of a GenericList based on a c++ model (inherit QAbstractListModel) to use with a QML ListView. It is oriented towards others repositorys [Kaldoon generic model](https://github.com/koldoon/qt-listview-generic-cpp-model) and [sgbo generic model](https://github.com/sgbo/QGenericListModel).
The generic list is implemented as a static library. You can also use the 5 files directly in your project. 

# How to use
You have to implement an specialised model and item with *Q_PROPERTY*(s). The name of the property is the same in QML. The specialised model is a wrapper for the generic model.

To register the generic model in the QML engine, you can use the macro **REGISTER_GENERIC_TYPES**( name of the plugin in QML ).