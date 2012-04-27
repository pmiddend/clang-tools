set(
	MODULE
	TRUE)

set(
	LLVM_USED_LIBS
	clangFrontend
	clangAST)

set(
	LLVM_LINK_COMPONENTS
	support
	mc)

include_directories(
	include/)

add_clang_library(
	sgestyle
	src/sgestyle/plugin_action.cpp
	src/sgestyle/consumer.cpp)

set_target_properties(
	sgestyle
	PROPERTIES
	LINKER_LANGUAGE CXX
	PREFIX "")
