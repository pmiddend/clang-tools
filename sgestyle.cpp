//===- PrintFunctionNames.cpp ---------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Example clang plugin which simply prints the names of all the top-level decls
// in the input file.
//
//===----------------------------------------------------------------------===//

#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/AST.h"
#include "clang/Frontend/CompilerInstance.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>

using namespace clang;

namespace {

class SGEStyleConsumer
:
	public ASTConsumer
{
public:
	void
	HandleTagDeclDefinition(
		TagDecl *);
};

void
SGEStyleConsumer::HandleTagDeclDefinition(TagDecl *d)
{
	if (const CXXRecordDecl *ND = dyn_cast<CXXRecordDecl>(d))
	{
		for(CXXRecordDecl::ctor_iterator it = ND->ctor_begin(); it != ND->ctor_end(); ++it)
		{
			if(it->isExplicit())
			{
			      if(it->getMinRequiredArguments() != 1)
			      {
				      Decl const *rawDeclContext = ND->getTranslationUnitDecl();
				      if(rawDeclContext)
					      llvm::errs() << "We have a context\n";

					if(const NamespaceDecl *DeclContext = dyn_cast<NamespaceDecl>(ND->getDeclContext()))
					{
						llvm::errs()
							<< "Context: "
							<< DeclContext->getNameAsString();
					}

					llvm::errs()
						<< ND->getNameAsString()
						<< ": ctor is explicit, but requires "
						<< it->getMinRequiredArguments()
						<< " arguments\n";
			      }
			}
			else
			{
				if(it->getMinRequiredArguments() == 1)
					llvm::errs()
						<< ND->getNameAsString()
						<< ": ctor is implicit, but can be called with 1 argument!\n";
			}
		}
	}

	ASTConsumer::HandleTagDeclDefinition(
		d);
}

class SGEStyleAction : public PluginASTAction {
protected:
  ASTConsumer *CreateASTConsumer(CompilerInstance &CI, llvm::StringRef) {
    return new SGEStyleConsumer();
  }

  bool ParseArgs(const CompilerInstance &CI,
                 const std::vector<std::string>& args) {
    for (unsigned i = 0, e = args.size(); i != e; ++i) {
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
  }
  void PrintHelp(llvm::raw_ostream& ros) {
    ros << "Help for PrintFunctionNames plugin goes here\n";
  }

};

}

static FrontendPluginRegistry::Add<SGEStyleAction> X("print-sge-style", "Warn pedantically about sge style issues");
