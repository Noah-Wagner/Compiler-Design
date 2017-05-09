//
// Created by Steve on 1/May/2017.
//

#ifndef STEVE_JVMCODEGEN_H
#define STEVE_JVMCODEGEN_H

#include <iostream>
#include <sstream>
#include "CodeGen.h"

struct JVMCodeGen : CodeGen {

	static JVMCodeGen * instance;

	std::stringstream ss;

	static JVMCodeGen * GetGenerator() {
		if (JVMCodeGen::instance == nullptr) {
			return new JVMCodeGen();
		}
		return JVMCodeGen::instance;
	}

	static std::stringstream * GetSS() {
		return &GetGenerator()->ss;
	}


	void Generate(std::vector<Stmt *> vector) override {

		for (int i = 0; i < vector.size(); i++) {
			ExprStmt * stmt = (ExprStmt *) vector[i];
			GenerateDecl(stmt->expr);
		}

	}

	static void GenerateDecl(Expr * expr) {

		struct V : Expr::Visitor {

			void visit(BoolExpr * e) {
				*GetSS() << "iconst_" << (e->val ? "1" : "0");
			};

			void visit(AndExpr * e) {

				GenerateDecl(e->e1);
				GenerateDecl(e->e2);

				*GetSS() << "iand";

			};

			void visit(OrExpr * e) {

				GenerateDecl(e->e1);
				GenerateDecl(e->e2);

				*GetSS() << "ior";

			};

			void visit(BitAndExpr * e) {

				GenerateDecl(e->e1);
				GenerateDecl(e->e2);

				*GetSS() << "iand";

			};

			void visit(BitOrExpr * e) {

				GenerateDecl(e->e1);
				GenerateDecl(e->e2);

				*GetSS() << "ior";

			};

			void visit(BitXorExpr * e) {

				GenerateDecl(e->e1);
				GenerateDecl(e->e2);

				*GetSS() << "ixor";

			};

			void visit(NotExpr * e) {

				GenerateDecl(e->e1);

				*GetSS() << "iconst_1";
				*GetSS() << "ixor";

			}

			void visit(IntExpr * e) {

				*GetSS() << "iconst_" << e->val;

			}

			void visit(AddExpr * e) {

				GenerateDecl(e->e1);
				GenerateDecl(e->e2);

				*GetSS() << "iadd";

			}

			void visit(SubExpr * e) {

				GenerateDecl(e->e1);
				GenerateDecl(e->e2);

				*GetSS() << "isub";

			}

			void visit(MultiExpr * e) {

				GenerateDecl(e->e1);
				GenerateDecl(e->e2);

				*GetSS() << "imul";

			}

			void visit(DivExpr * e) {

				GenerateDecl(e->e1);
				GenerateDecl(e->e2);

				*GetSS() << "idiv";

			}

			void visit(ModExpr * e) {

				GenerateDecl(e->e1);
				GenerateDecl(e->e2);

				*GetSS() << "irem";

			}

			void visit(EqExpr * e) {

				GenerateDecl(e->e1);
				GenerateDecl(e->e2);

				*GetSS() << "if_icmpeq";

			}

			void visit(NeqExpr * e) {

				GenerateDecl(e->e1);
				GenerateDecl(e->e2);

				*GetSS() << "if_icmpeq";

			}

			void visit(GeExpr * e) {

				GenerateDecl(e->e1);
				GenerateDecl(e->e2);

				*GetSS() << "if_icmpgt";

			}

			void visit(GeqExpr * e) {

				GenerateDecl(e->e1);
				GenerateDecl(e->e2);

				*GetSS() << "if_icmpge";

			}

			void visit(LeExpr * e) {

				GenerateDecl(e->e1);
				GenerateDecl(e->e2);

				*GetSS() << "if_icmplt";

			}

			void visit(LeqExpr * e) {

				GenerateDecl(e->e1);
				GenerateDecl(e->e2);

				*GetSS() << "if_icmple";

			}

			void visit(NegExpr * e) {

				GenerateDecl(e->e1);

				*GetSS() << "iconst_1";
				*GetSS() << "ixor";

			}

			void visit(AssignExpr * e) {

				GenerateDecl(e->rval);

				*GetSS() << "istore_0";

			}

			void visit(VarExpr * e) {

				// more work here needed

			}

			void visit(CondExpr *e) {

			}

			void visit(AndThenExpr *e) {

			}

			void visit(OrElseExpr *e) {

			}

		};

		V visitor;
		expr->accept(visitor);
	}

};

JVMCodeGen * JVMCodeGen::instance;

#endif //STEVE_JVMCODEGEN_H
