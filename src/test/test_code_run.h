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

#ifndef __TEST_CODE_RUN_H__
#define __TEST_CODE_RUN_H__

#include <test/test_base.h>

///////////////////////////////////////////////////////////////////////////////

/**
 * Testing PHP -> C++ -> execution.
 */
class TestCodeRun : public TestBase {
 public:
  TestCodeRun();

  virtual bool RunTests(const std::string &which);

  // test test harness
  bool TestSanity();

  // test code generation process
  bool TestInnerFunction();
  bool TestInnerClass();
  bool TestVariableArgument();
  bool TestListAssignment();
  bool TestExceptions();
  bool TestPredefined();

  // test types
  bool TestBoolean();
  bool TestInteger();
  bool TestDouble();
  bool TestString();
  bool TestArray();
  bool TestArrayEscalation();
  bool TestArrayOffset();
  bool TestArrayAccess();
  bool TestArrayIterator();
  bool TestArrayAssignment();
  bool TestArrayMerge();
  bool TestArrayUnique();
  bool TestScalarArray();
  bool TestRange();
  bool TestVariant();
  bool TestObject();
  bool TestObjectProperty();
  bool TestObjectMethod();
  bool TestClassMethod();
  bool TestObjectMagicMethod();
  bool TestObjectAssignment();
  bool TestNewObjectExpression();
  bool TestObjectPropertyExpression();
  bool TestComparisons();
  bool TestTernary();
  bool TestTypes();
  bool TestSwitchStatement();

  // test semantics
  bool TestUnset();
  bool TestReference();
  bool TestDynamicConstants();
  bool TestDynamicVariables();
  bool TestDynamicProperties();
  bool TestDynamicFunctions();
  bool TestDynamicMethods();
  bool TestVolatile();
  bool TestSuperGlobals();
  bool TestGlobalStatement();
  bool TestStaticStatement();
  bool TestIfStatement();
  bool TestBreakStatement();
  bool TestContinueStatement();
  bool TestReturnStatement();
  bool TestAdd();
  bool TestMinus();
  bool TestMultiply();
  bool TestDivide();
  bool TestModulus();
  bool TestOperationTypes();
  bool TestUnaryOperators();
  bool TestSilenceOperator();
  bool TestLogicalOperators();
  bool TestGetClass();
  bool TestGetParentClass();
  bool TestRedeclaredFunctions();
  bool TestRedeclaredClasses();
  bool TestClone();
  bool TestEvalOrder();
  bool TestGetObjectVars();
  bool TestSerialization();
  bool TestJson();
  bool TestExit();
  bool TestConstructorDestructor();
  bool TestConcat();
  bool TestConstant();
  bool TestClassConstant();
  bool TestConstantFunction();
  bool TestDefined();
  bool TestAssignment();
  bool TestEvaluationOrder();
  bool TestPrint();
  bool TestLocale();
  bool TestBadFunctionCalls();
  bool TestConstructor();

  // misc
  bool TestProgramFunctions();
  bool TestCompilation();
  bool TestReflection();
  bool TestReflectionClasses();
  bool TestErrorHandler();
  bool TestAssertOptions();
  bool TestExtMisc();
  bool TestThrift();
  bool TestCreateFunction();
  bool TestSimpleXML();
  bool TestFile();
  bool TestUselessAssignment();
  bool TestExtImage();

  // debugging purpose
  bool TestAdHoc();

 protected:
  bool CleanUp();
  bool GenerateFiles(const char *input);
  bool CompileFiles(const char *input, const char *file, int line);

  bool VerifyCodeRun(const char *input, const char *output,
                     const char *file = "", int line = 0,
                     bool nowarnings = false);

  bool m_perfMode;
};

///////////////////////////////////////////////////////////////////////////////
// macros

#define VCR(a) \
  if (!Count(VerifyCodeRun(a,NULL,__FILE__,__LINE__))) return false;

#define VCRNW(a) \
  if (!Count(VerifyCodeRun(a,NULL,__FILE__,__LINE__,true))) return false;

///////////////////////////////////////////////////////////////////////////////

#endif // __TEST_CODE_RUN_H__