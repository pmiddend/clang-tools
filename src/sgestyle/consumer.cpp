#include <sgestyle/consumer.hpp>
#include <llvm/Support/Casting.h>
#include <clang/AST/DeclCXX.h>
#include <clang/AST/Decl.h>
#include <clang/AST/ASTContext.h>
#include <clang/Basic/SourceManager.h>

void
sgestyle::consumer::HandleTagDeclDefinition(
	clang::TagDecl * const d)
{
	clang::SourceManager &source_manager =
		d->getASTContext().getSourceManager();

	// TODO: Implement file name filter here
	char const *file_name =
		source_manager.getBufferName(
			d->getLocation());

	if (clang::CXXRecordDecl const *ND = llvm::dyn_cast<clang::CXXRecordDecl>(d))
		this->handle_record_definition(
			*ND);

	ASTConsumer::HandleTagDeclDefinition(
		d);
}

void
sgestyle::consumer::handle_record_definition(
	clang::CXXRecordDecl const &_record)
{
	this->check_implicit_ctors(
		_record);

	this->check_member_names(
		_record);
}

void
sgestyle::consumer::check_implicit_ctors(
	clang::CXXRecordDecl const &_record)
{
	for(
		clang::CXXRecordDecl::ctor_iterator it =
			_record.ctor_begin();
		it != _record.ctor_end();
		++it)
	{
		clang::SourceManager &source_manager =
			_record.getASTContext().getSourceManager();

		if(it->isExplicit())
		{
			if(it->getMinRequiredArguments() == 1)
				continue;

			it->getLocation().print(
				llvm::errs(),
				source_manager);

			llvm::errs()
				<< ": Constructor for class \""
				<< _record.getNameAsString()
				<< "\" is explicit, but requires "
				<< it->getMinRequiredArguments()
				<< " arguments\n";
		}
		else
		{
			if(it->getMinRequiredArguments() != 1)
				continue;

			it->getLocation().print(
				llvm::errs(),
				source_manager);

			llvm::errs()
				<< ": Constructor for class \""
				<< _record.getNameAsString()
				<< "\" is implicit, but can be called with 1 argument\n";
		}
	}
}

void
sgestyle::consumer::check_member_names(
	clang::CXXRecordDecl const &_record)
{
	for(
		clang::CXXRecordDecl::field_iterator it =
			_record.field_begin();
		it != _record.field_end();
		++it)
	{
		std::string const field_name = it->getNameAsString();

		if(field_name[field_name.size()-1u] == '_')
			continue;

		clang::SourceManager &source_manager =
			_record.getASTContext().getSourceManager();

		it->getLocation().print(
			llvm::errs(),
			source_manager);

		llvm::errs()
			<< ": member \""
			<< field_name
			<< "\" of class \""
			<< _record.getNameAsString()
			<< "\" doesn't end with an underscore\n";
	}
}
