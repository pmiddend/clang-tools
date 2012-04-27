#ifndef SGESTYLE_PLUGIN_ACTION_HPP_INCLUDED
#define SGESTYLE_PLUGIN_ACTION_HPP_INCLUDED

#include <clang/Frontend/FrontendAction.h>

namespace sgestyle
{
class plugin_action
:
	public clang::PluginASTAction
{
protected:
	clang::ASTConsumer *
	CreateASTConsumer(
		clang::CompilerInstance &CI,
		llvm::StringRef);

	bool
	ParseArgs(
		clang::CompilerInstance const &,
		std::vector<std::string> const &);

	void
	PrintHelp(
		llvm::raw_ostream &);
};
}

#endif

