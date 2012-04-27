#ifndef SGESTYLE_CONSUMER_HPP_INCLUDED
#define SGESTYLE_CONSUMER_HPP_INCLUDED

#include "clang/AST/ASTConsumer.h"

namespace sgestyle
{
class consumer
:
	public clang::ASTConsumer
{
public:
	void
	HandleTagDeclDefinition(
		clang::TagDecl *);
private:
	void
	handle_record_definition(
		clang::CXXRecordDecl const &);

	void
	check_implicit_ctors(
		clang::CXXRecordDecl const &);

	void
	check_member_names(
		clang::CXXRecordDecl const &);
};
}

#endif

