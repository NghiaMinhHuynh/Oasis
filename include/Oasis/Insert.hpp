// Insert.hpp
// Free functions for persistent O(log N) associative inserts into Oasis expression trees.

#ifndef OASIS_INSERT_HPP
#define OASIS_INSERT_HPP

#include <memory>
#include "Expression.hpp"
#include "Add.hpp"
#include "Multiply.hpp"

namespace Oasis {

/**
 * Inserts `value` into an Add expression tree at `root`, rebalancing via direction flags.
 * If `root` is not an Add node, wraps `(root + value)` with initial dir=false.
 */
inline std::shared_ptr<Expression>
insertAdd(const std::shared_ptr<Expression>& root,
          const std::shared_ptr<Expression>& value) {
    using AddExpr = Add<Expression, Expression>;
    // Not an Add: create new root Add node
    if (root->GetType() != ExpressionType::Add) {
        return std::make_shared<AddExpr>(root, value, false);
    }
    // Cast to shared Add
    auto A = std::static_pointer_cast<AddExpr>(root);
    bool dir = A->dir();
    if (dir) {
        // insert on right
        auto newRight = insertAdd(A->GetLeastSigOp(), value);
        return A->copy_with_dir(!dir)->withChildren(A->GetMostSigOp(), newRight);
    } else {
        // insert on left
        auto newLeft = insertAdd(A->GetMostSigOp(), value);
        return A->copy_with_dir(!dir)->withChildren(newLeft, A->GetLeastSigOp());
    }
}

/**
 * Inserts `value` into a Multiply expression tree at `root`, rebalancing via direction flags.
 * If `root` is not a Multiply node, wraps `(root * value)` with initial dir=false.
 */
inline std::shared_ptr<Expression>
insertMul(const std::shared_ptr<Expression>& root,
          const std::shared_ptr<Expression>& value) {
    using MulExpr = Multiply<Expression, Expression>;
    if (root->GetType() != ExpressionType::Multiply) {
        return std::make_shared<MulExpr>(root, value, false);
    }
    auto M = std::static_pointer_cast<MulExpr>(root);
    bool dir = M->dir();
    if (dir) {
        auto newRight = insertMul(M->GetLeastSigOp(), value);
        return M->copy_with_dir(!dir)->withChildren(M->GetMostSigOp(), newRight);
    } else {
        auto newLeft = insertMul(M->GetMostSigOp(), value);
        return M->copy_with_dir(!dir)->withChildren(newLeft, M->GetLeastSigOp());
    }
}

} // namespace Oasis

#endif // OASIS_INSERT_HPP
