/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010 Facebook, Inc. (http://www.facebook.com)          |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#include <lib/statement/if_branch_statement.h>
#include <lib/expression/constant_expression.h>

using namespace HPHP;
using namespace std;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// constructors/destructors

IfBranchStatement::IfBranchStatement
(STATEMENT_CONSTRUCTOR_PARAMETERS,
 ExpressionPtr condition, StatementPtr stmt)
  : Statement(STATEMENT_CONSTRUCTOR_PARAMETER_VALUES),
    m_condition(condition), m_stmt(stmt) {
}

StatementPtr IfBranchStatement::clone() {
  IfBranchStatementPtr stmt(new IfBranchStatement(*this));
  stmt->m_condition = Clone(m_condition);
  stmt->m_stmt = Clone(m_stmt);
  return stmt;
}

///////////////////////////////////////////////////////////////////////////////
// parser functions

///////////////////////////////////////////////////////////////////////////////
// static analysis functions

void IfBranchStatement::analyzeProgram(AnalysisResultPtr ar) {
  if (m_condition) m_condition->analyzeProgram(ar);
  if (m_stmt) m_stmt->analyzeProgram(ar);
}

StatementPtr IfBranchStatement::preOptimize(AnalysisResultPtr ar) {
  ar->preOptimize(m_condition);
  ar->preOptimize(m_stmt);
  return StatementPtr();
}

StatementPtr IfBranchStatement::postOptimize(AnalysisResultPtr ar) {
  ar->postOptimize(m_condition);
  ar->postOptimize(m_stmt);
  return StatementPtr();
}

void IfBranchStatement::inferTypes(AnalysisResultPtr ar) {
  if (m_condition) m_condition->inferAndCheck(ar, Type::Boolean, false);
  if (m_stmt) m_stmt->inferTypes(ar);
}

///////////////////////////////////////////////////////////////////////////////
// code generation functions

void IfBranchStatement::outputPHP(CodeGenerator &cg, AnalysisResultPtr ar) {
  if (m_condition) {
    cg.printf("if (");
    m_condition->outputPHP(cg, ar);
    cg.printf(") ");
  } else {
    cg.printf(" ");
  }
  if (m_stmt) {
    m_stmt->outputPHP(cg, ar);
  } else {
    cg.printf("{}\n");
  }
}

void IfBranchStatement::outputCPP(CodeGenerator &cg, AnalysisResultPtr ar) {
  if (m_condition) {
    cg.printf("if (");
    m_condition->outputCPP(cg, ar);
    cg.printf(") ");
  }
  if (m_stmt) {
    m_stmt->outputCPP(cg, ar);
  } else {
    cg.printf("{}\n");
  }
}