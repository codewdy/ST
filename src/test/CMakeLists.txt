new_executable(test)
TARGET_LINK_LIBRARIES(test Parser AST STC Runtime BaseType BuiltinType Exception)

new_copy_only(test.st test.st)
ADD_DEPENDENCIES(test test.st)
