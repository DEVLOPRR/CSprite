#ifndef CSP_DOC_PARSER_PARSER_HPP_INCLUDED_
#define CSP_DOC_PARSER_PARSER_HPP_INCLUDED_
#pragma once

#include "types.hpp"
#include "doc/doc.hpp"

namespace Parser {
	bool ParseImageFile(Doc& doc, const String filePath);
}

#endif // CSP_DOC_PARSER_PARSER_HPP_INCLUDED_
