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

#ifndef __OBJECT_PROPERTY_EXPRESSION_H__
#define __OBJECT_PROPERTY_EXPRESSION_H__

#include <compiler/expression/expression.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

DECLARE_BOOST_TYPES(ExpressionList);
DECLARE_BOOST_TYPES(ObjectPropertyExpression);
DECLARE_BOOST_TYPES(ClassScope);
class Symbol;

class ObjectPropertyExpression : public Expression {
public:
  ObjectPropertyExpression(EXPRESSION_CONSTRUCTOR_PARAMETERS,
                           ExpressionPtr object, ExpressionPtr property);

  DECLARE_EXPRESSION_VIRTUAL_FUNCTIONS;
  virtual int getLocalEffects() const { return m_localEffects; }
  virtual bool isRefable(bool checkError = false) const { return true;}

  virtual void setContext(Context context);
  virtual void clearContext(Context context);

  ExpressionPtr getObject() { return m_object;}
  ExpressionPtr getProperty() { return m_property;}

  virtual void outputCPPExistTest(CodeGenerator &cg, AnalysisResultPtr ar,
                                  int op);
  virtual void outputCPPUnset(CodeGenerator &cg, AnalysisResultPtr ar);
  void preOutputStash(CodeGenerator &cg, AnalysisResultPtr ar, int state);
  bool preOutputCPP(CodeGenerator &cg, AnalysisResultPtr ar, int state);
  bool isTemporary() const;
  bool isNonPrivate(AnalysisResultPtr ar) const;
  bool isValid() const { return m_valid; }
  void outputCPPProperty(CodeGenerator &cg, AnalysisResultPtr ar);
  void outputCPPObject(CodeGenerator &cg, AnalysisResultPtr ar,
                       int directVariant = -1);
private:
  void setEffect(Effect effect);
  void clearEffect(Effect effect);

  ExpressionPtr m_object;
  ExpressionPtr m_property;

  unsigned m_valid : 1;
  unsigned m_propSymValid : 1;

  int m_localEffects;
  std::string m_lvalTmp;

  Symbol *m_propSym;
  boost::weak_ptr<HPHP::ClassScope> m_objectClass;

  // for avoiding code generate toObject(Variant)
  bool directVariantProxy(AnalysisResultPtr ar);
  void outputCPPObjProperty(CodeGenerator &cg, AnalysisResultPtr ar,
                            bool directVariant, int doExist);
};

///////////////////////////////////////////////////////////////////////////////
}
#endif // __OBJECT_PROPERTY_EXPRESSION_H__
