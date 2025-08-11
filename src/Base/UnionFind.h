//
// Created by Administrator on 2025/8/5.
//

#ifndef UNIONFIND_H
#define UNIONFIND_H
#include "../ThirdParty.h"
namespace FCT {
    template<typename T,typename ShareType = void>
    class UnionFind {
    private:
        mutable std::unordered_map<T, T> m_parent;
        mutable std::unordered_map<T, int> m_rank;
        mutable std::conditional_t<!std::is_void_v<ShareType>,
                                  std::unordered_map<T, std::optional<ShareType>>,
                                  char> m_sharedData;
    public:

        T find(const T& x) const {
            if (m_parent.find(x) == m_parent.end()) {
                m_parent[x] = x;
                m_rank[x] = 0;
                if constexpr (!std::is_void_v<ShareType>) {
                    m_sharedData[x] = std::nullopt;
                }
                return x;
            }

            if (m_parent[x] != x) {
                m_parent[x] = find(m_parent[x]);
            }
            return m_parent[x];
        }

        bool unite(const T& x, const T& y) {
            T rootX = find(x);
            T rootY = find(y);

            if (rootX == rootY) return false;

            if (m_rank[rootX] < m_rank[rootY]) {
                m_parent[rootX] = rootY;
                if constexpr (!std::is_void_v<ShareType>) {
                    if (!m_sharedData[rootY].has_value() && m_sharedData[rootX].has_value()) {
                        m_sharedData[rootY] = m_sharedData[rootX];
                    }
                }
            } else if (m_rank[rootX] > m_rank[rootY]) {
                m_parent[rootY] = rootX;
                if constexpr (!std::is_void_v<ShareType>) {
                    if (!m_sharedData[rootX].has_value() && m_sharedData[rootY].has_value()) {
                        m_sharedData[rootX] = m_sharedData[rootY];
                    }
                }
            } else {
                m_parent[rootY] = rootX;
                m_rank[rootX]++;
                if constexpr (!std::is_void_v<ShareType>) {
                    if (!m_sharedData[rootX].has_value() && m_sharedData[rootY].has_value()) {
                        m_sharedData[rootX] = m_sharedData[rootY];
                    }
                }
            }
            return true;
        }

        std::unordered_map<T, std::vector<T>> getGroups() const {
            std::unordered_map<T, std::vector<T>> groups;

            for (const auto& [element, _] : m_parent) {
                T root = find(element);
                groups[root].push_back(element);
            }

            return groups;
        }
        bool connected(const T& x, const T& y) const {
            return find(x) == find(y);
        }
        void shared(const T& x, const ShareType& data)
       requires (!std::is_void_v<ShareType>)
        {
            T root = find(x);
            m_sharedData[root] = data;
        }

        std::optional<ShareType> shared(const T& x) const
            requires (!std::is_void_v<ShareType>)
        {
            T root = find(x);
            auto it = m_sharedData.find(root);
            return (it != m_sharedData.end()) ? it->second : std::nullopt;
        }
    };
};// namespace FCT
#endif //UNIONFIND_H
