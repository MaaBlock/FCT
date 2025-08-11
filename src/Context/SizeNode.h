#ifndef SIZENODE_H
#define SIZENODE_H
#include "../Base/FractionScale2D.h"
namespace FCT
{
    struct SizeNode {
        virtual ~SizeNode() = default;
        mutable SizeNode* parent;
        mutable uint32_t width;
        mutable uint32_t height;
        mutable bool sizeFixed;         // 大小是否已固定（不能再改变）
        mutable FractionScale2D scaleToParent;  // 相对于父节点的缩放比例

        SizeNode() noexcept
            : parent(this), width(0), height(0), sizeFixed(false), scaleToParent() {}

        SizeNode(uint32_t w, uint32_t h) noexcept
            : parent(this), width(w), height(h), sizeFixed(true), scaleToParent() {}

        SizeNode* findRoot() const noexcept {
            if (parent != this) {
                FractionScale2D oldScale = scaleToParent;
                parent = parent->findRoot();
                scaleToParent = oldScale * parent->scaleToParent;
            }
            return parent;
        }

        FractionScale2D getScaleToRoot() const noexcept {
            if (parent == this) {
                return FractionScale2D();
            }

            findRoot();
            return scaleToParent;
        }
        /**
          * @cond CHINESE
          * 将当前节点与另一个节点合并到同一个大小组中
          * @param other 要合并的目标节点
          * @param scale 当前节点相对于目标节点的缩放比例 (this_size = other_size * scale)
          * @return 合并是否成功，如果两个节点已经在同一组但缩放比例不匹配则返回false
          * @endcond
          */
        bool unite(SizeNode* other, const FractionScale2D& scale = FractionScale2D()) const noexcept {
            SizeNode* rootA = findRoot();
            SizeNode* rootB = other->findRoot();

            if (rootA == rootB) {
                FractionScale2D expectedScale = getScaleToRoot() / other->getScaleToRoot();
                return expectedScale == scale;
            }

            SizeNode* newRoot;
            SizeNode* childRoot;
            FractionScale2D childScale;

            if (rootA->sizeFixed && !rootB->sizeFixed) {
                newRoot = rootA;
                childRoot = rootB;
                FractionScale2D thisScale = getScaleToRoot();
                FractionScale2D otherScale = other->getScaleToRoot();
                childScale = thisScale / (otherScale * scale);
            } else if (!rootA->sizeFixed && rootB->sizeFixed) {
                newRoot = rootB;
                childRoot = rootA;
                FractionScale2D thisScale = getScaleToRoot();
                FractionScale2D otherScale = other->getScaleToRoot();
                childScale = (otherScale * scale) / thisScale;
            } else if (rootA->sizeFixed && rootB->sizeFixed) {
                FractionScale2D thisScale = getScaleToRoot();
                FractionScale2D otherScale = other->getScaleToRoot();

                uint32_t expectedWidth = static_cast<uint32_t>(
                    rootB->width * otherScale.width.toFloat() * scale.width.toFloat() / thisScale.width.toFloat()
                );
                uint32_t expectedHeight = static_cast<uint32_t>(
                    rootB->height * otherScale.height.toFloat() * scale.height.toFloat() / thisScale.height.toFloat()
                );

                if (rootA->width != expectedWidth || rootA->height != expectedHeight) {
                    return false;
                }

                newRoot = rootA;
                childRoot = rootB;
                childScale = (otherScale * scale) / thisScale;
            } else {
                newRoot = rootA;
                childRoot = rootB;
                FractionScale2D thisScale = getScaleToRoot();
                FractionScale2D otherScale = other->getScaleToRoot();
                childScale = (otherScale * scale) / thisScale;
            }

            childRoot->parent = newRoot;
            childRoot->scaleToParent = childScale;

            return true;
        }

        bool setFixed() const noexcept {
            SizeNode* root = findRoot();

            if (root->sizeFixed) {
                return false;
            }

            root->sizeFixed = true;
            root->width = 0;
            root->height = 0;

            return true;
        }

        bool setFixedSize(uint32_t w, uint32_t h) const noexcept {
            SizeNode* root = findRoot();

            if (root->sizeFixed) {
                FractionScale2D scale = getScaleToRoot();
                uint32_t expectedWidth = static_cast<uint32_t>(root->width * scale.width.toFloat());
                uint32_t expectedHeight = static_cast<uint32_t>(root->height * scale.height.toFloat());

                return (expectedWidth == w && expectedHeight == h);
            }

            FractionScale2D scale = getScaleToRoot();
            root->width = static_cast<uint32_t>(w / scale.width.toFloat());
            root->height = static_cast<uint32_t>(h / scale.height.toFloat());
            root->sizeFixed = true;

            return true;
        }

        bool getComputedSize(uint32_t& w, uint32_t& h) const noexcept {
            SizeNode* root = findRoot();

            if (!root->sizeFixed) {
                return false;
            }

            FractionScale2D scale = getScaleToRoot();
            w = static_cast<uint32_t>(root->width * scale.width.toFloat());
            h = static_cast<uint32_t>(root->height * scale.height.toFloat());

            return true;
        }

        bool isSizeDetermined() const noexcept {
            return findRoot()->sizeFixed;
        }

        const SizeNode* getRoot() const noexcept {
            return findRoot();
        }

        bool isConnected(const SizeNode* other) const noexcept {
            return findRoot() == other->findRoot();
        }
        bool isSameSize(const SizeNode* other) const noexcept
        {
            return findRoot() == other->findRoot() && getScaleToRoot() == other->getScaleToRoot();
        }

        FractionScale2D getRelativeScale(const SizeNode* other) const noexcept {
            if (!isConnected(other)) {
                return FractionScale2D(Fraction(0, 1), Fraction(0, 1));
            }

            return getScaleToRoot() / other->getScaleToRoot();
        }
    };
} // namespace FCT
#endif //SIZENODE_H