#include <sgestyle/plugin_action.hpp>
#include <sgestyle/consumer.hpp>
#include <clang/Frontend/FrontendPluginRegistry.h>

clang::ASTConsumer *
sgestyle::plugin_action::CreateASTConsumer(
	clang::CompilerInstance &CI,
	llvm::StringRef)
{
	return new sgestyle::consumer();
}

bool
sgestyle::plugin_action::ParseArgs(
	clang::CompilerInstance const &CI,
	std::vector<std::string> const &args)
{
	return
		true;
	/*
	for (unsigned i = 0, e = args.size(); i != e; ++i)
	{
	llvm::errs() << "PrintFunctionNames arg = " << args[i] << "\n";

	// Example error handling.
	if (args[i] == "-an-error") {
	DiagnosticsEngine &D = CI.getDiagnostics();
	unsigned DiagID = D.getCustomDiagID(
	  DiagnosticsEngine::Error, "invalid argument '" + args[i] + "'");
	D.Report(DiagID);
	return false;
	}
	}
	if (args.size() && args[0] == "help")
	PrintHelp(llvm::errs());

	return true;
	*/
}

void
sgestyle::plugin_action::PrintHelp(llvm::raw_ostream& ros)
{
	ros << "Help goes here\n";
}

static clang::FrontendPluginRegistry::Add<sgestyle::plugin_action> X("print-sge-style", "Warn pedantically about sge style issues");
