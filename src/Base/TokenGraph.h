//
// Created by Administrator on 2025/7/23.
//

#ifndef TOKENGRAPH_H
#define TOKENGRAPH_H
#include "../ThirdParty.h"
#include "Noncopyable.h"
namespace FCT {
	template<typename Token,typename Value>
	class TokenGraph : public Noncopyable
	{
	private:
		class NodeProbe;
		struct NodeInfo
		{
		private:
			Token token;
			NodeInfo(Token token,Value value, std::vector<Token> predecessors, std::vector<Token> successors)
			{
				this->token = token;
                this->value = value;
                this->predecessors = predecessors;
                this->successors = successors;
			}
		public:
			friend class TokenGraph;
			friend class NodeProbe;
			NodeInfo(Value value, std::vector<Token> predecessors, std::vector<Token> successors)
			{
				this->value = value;
                this->predecessors = predecessors;
                this->successors = successors;
			}
			NodeInfo()
			{
                this->predecessors = std::vector<Token>();
                this->successors = std::vector<Token>();
			}
			Value value;
			std::vector<Token> predecessors;
			std::vector<Token> successors;
		};
		using TokenGraphSavedBoostGraph =
			boost::adjacency_list<
				boost::listS,
				boost::listS,
				boost::bidirectionalS,
				int, //weak ref
				int  //weak ref
		>;
		using BoostVertex = typename TokenGraphSavedBoostGraph::vertex_descriptor;
		void addVertex(Token token,int weak_ref = 0)
		{
			if (m_vertex.left.count(token))
				return;
			BoostVertex vertex = boost::add_vertex(weak_ref, m_graph);
			m_vertex.insert({token, vertex});
		}
		void removeVertex(Token token)
		{
			auto it = m_vertex.left.find(token);
			if (it != m_vertex.left.end()) {
				BoostVertex vertex = it->second;
				boost::remove_vertex(vertex, m_graph);
				m_vertex.left.erase(it);
			}
		}
		bool hasVertex(Token token) const
		{
			return m_vertex.left.count(token);
		}
		void addWeakRef(Token token)
		{
			auto it = m_vertex.left.find(token);
			if (it != m_vertex.left.end()) {
				++m_graph[it->second];
			}
		}
		void removeWeakRef(Token token)
		{
			auto it = m_vertex.left.find(token);
            if (it!= m_vertex.left.end()) {
                --m_graph[it->second];
            }
		}
		void addWeakRef(Token from, Token to)
		{
			auto from_it = m_vertex.left.find(from);
			auto to_it = m_vertex.left.find(to);

			if (from_it != m_vertex.left.end() && to_it != m_vertex.left.end()) {
				auto edge_pair = boost::edge(from_it->second, to_it->second, m_graph);
				if (edge_pair.second) {
					++m_graph[edge_pair.first];
				}
			}
		}
		void removeWeakRef(Token from, Token to)
		{
			auto from_it = m_vertex.left.find(from);
			auto to_it = m_vertex.left.find(to);

			if (from_it != m_vertex.left.end() && to_it != m_vertex.left.end()) {
				auto edge_pair = boost::edge(from_it->second, to_it->second, m_graph);
				if (edge_pair.second) {
					--m_graph[edge_pair.first];
					if (m_graph[edge_pair.first])
						return;
					removeBoostEdge(from,to);
				}
			}
		}
		bool hasEdge(Token from, Token to) const
		{
			auto from_it = m_vertex.left.find(from);
			auto to_it = m_vertex.left.find(to);

			if (from_it != m_vertex.left.end() && to_it != m_vertex.left.end()) {
				auto edge_pair = boost::edge(from_it->second, to_it->second, m_graph);
				return edge_pair.second;
			}
			return false;
		}
		bool hasNode(Token token) const
		{
			return m_nodeMap.count(token);
		}
		void addBoostEdge(Token from, Token to)
		{
			boost::add_edge(m_vertex.left.at(from), m_vertex.left.at(to), 1, m_graph);
		}
		void removeBoostEdge(Token from, Token to)
		{
			auto from_it = m_vertex.left.find(from);
            auto to_it = m_vertex.left.find(to);
            if (from_it!= m_vertex.left.end() && to_it!= m_vertex.left.end())
            {
            	auto edge_pair = boost::edge(from_it->second, to_it->second, m_graph);
            	if (edge_pair.second)
            	{
            		boost::remove_edge(edge_pair.first, m_graph);
            	}
                //boost::remove_edge(from_it->second, to_it->second, m_graph);
            }
		}
		void addEdge(Token node, Token rhs,bool isSuccessor)
		{
			if (hasVertex(rhs))
			{
				addWeakRef(rhs);
			} else
			{
				addVertex(rhs,1);
			}
			if (isSuccessor)
			{
				if (hasEdge(node, rhs))
				{
					addWeakRef(node,rhs);
				} else
				{
					addBoostEdge(node, rhs);
				}
			} else
			{
				if (hasEdge(rhs, node))
                {
                    addWeakRef(rhs, node);
                } else
                {
                    addBoostEdge(rhs, node);
                }
			}
		}


		template<typename Visitor>
		class TokenGraphBFSVisitor : public boost::default_bfs_visitor
		{
		private:
			const TokenGraph* graph;
			Visitor visitor;
			Token startToken;
			bool includeStart;

		public:
			TokenGraphBFSVisitor(const TokenGraph* g, Visitor v, Token start, bool include)
				: graph(g), visitor(v), startToken(start), includeStart(include) {}

			template<typename VertexDescriptor, typename Graph>
			void discover_vertex(VertexDescriptor v, const Graph& g) const
			{
				auto vertex_token_it = graph->m_vertex.right.find(v);
				if (vertex_token_it != graph->m_vertex.right.end()) {
					Token token = vertex_token_it->second;
					if (graph->hasNode(token)) {
						if (!includeStart && token == startToken) {
							return;
						}
						visitor(graph->m_nodeMap.at(token).value);
					}
				}
			}
		};
		bool isZeroRefVertex(Token token) const
		{
			auto it = m_vertex.left.find(token);
            return m_graph[it->second] == 0;
		}

		void removeEdge(Token node, Token rhs,bool isSuccessor)
		{
			if (isSuccessor)
            {
                if (hasEdge(node, rhs))
                {
                    removeWeakRef(node, rhs);
                }
            } else
            {
                if (hasEdge(rhs, node))
                {
                    removeWeakRef(rhs, node);
                }
            }
			removeWeakRef(rhs);
			if (isZeroRefVertex(rhs) && !hasNode(rhs))
			{
				removeVertex(rhs);
			}
		}
	public:

		/**
		 * @cond CHINESE
		 * @tparam Visitor
		 * @param startToken
		 * @param visitor 参数为 Value
		 * @param includeStart 是否包含起点自身
		 * @endcond
		 */
		template<typename Visitor>
		void visitBFS(Token startToken, Visitor visitor, bool includeStart = true) const
		{
			auto start_vertex_it = m_vertex.left.find(startToken);
			if (start_vertex_it == m_vertex.left.end()) {
				return;
			}

			std::map<BoostVertex, boost::default_color_type> vertex_color_map;
			auto color_pmap = boost::make_assoc_property_map(vertex_color_map);

			TokenGraphBFSVisitor<Visitor> bfs_visitor(this, visitor, startToken, includeStart);

			boost::breadth_first_search(m_graph, start_vertex_it->second,
				boost::visitor(bfs_visitor).color_map(color_pmap));
		}
		void addNode(NodeInfo info)
		{
			addVertex(info.token);
			m_nodeMap[info.token] = info;
			for (const auto& predecessor : info.predecessors) {
				addEdge( info.token,predecessor, false);
			}

			for (const auto& successor : info.successors) {
				addEdge(info.token, successor, true);
			}
		}
		void addNode(Token token,
					 Value value,
					 std::vector<Token> predecessors,
					 std::vector<Token> successors)
		{
			NodeInfo info = { token, value, predecessors, successors };
			addNode(info);
		}
		void removeNode(const Token& token)
		{
            for (const auto& predecessor : m_nodeMap[token].predecessors)
            {
                removeEdge(predecessor, token, false);
            }
            for (const auto& successor : m_nodeMap[token].successors)
            {
                removeEdge(token, successor, true);
            }
			m_nodeMap.erase(token);
			if (isZeroRefVertex(token))
			{
				removeVertex(token);
			}
		}
		void update()
		{
			std::deque<BoostVertex> sortedVertices;

			std::map<BoostVertex, std::size_t> vertex_index_map;
			std::size_t index = 0;
			for (auto [v_iter, v_end] = boost::vertices(m_graph); v_iter != v_end; ++v_iter) {
				vertex_index_map[*v_iter] = index++;
			}
			auto index_pmap = boost::make_assoc_property_map(vertex_index_map);

			std::map<BoostVertex, boost::default_color_type> vertex_color_map;
			auto color_pmap = boost::make_assoc_property_map(vertex_color_map);

			boost::topological_sort(m_graph, std::front_inserter(sortedVertices),
								   boost::vertex_index_map(index_pmap).color_map(color_pmap));

			m_order.clear();

			for (auto vertex : sortedVertices) {
				auto it = m_vertex.right.find(vertex);
				if (it != m_vertex.right.end()) {
					Token token = it->second;
					if (hasNode(token)) {
						m_order.push_back(m_nodeMap[token].value);
					}
				}
			}
		}
		class NodeProbe
		{
		private:
			NodeProbe(TokenGraph& graph, Token token)
				: m_graph(graph), m_token(token), m_modified(false)
			{
				if (m_graph.m_nodeMap.find(token)!= m_graph.m_nodeMap.end())
				{
					m_nodeInfo = m_graph.m_nodeMap[token];
                    m_exists = true;
				} else
				{
					m_nodeInfo = {};
					m_exists = false;
				}
		   }
		public:
			friend class TokenGraph;
			~NodeProbe()
			{
				if (!m_exists)
				{
					if (m_modified)
					{
						m_nodeInfo.token = m_token;
						m_graph.addNode(m_nodeInfo);
					}
					return;
				}
				if (m_modified) {
					m_graph.updateNode(m_nodeInfo);
				}
			}
			NodeProbe(const NodeProbe&) = delete;
			NodeProbe& operator=(const NodeProbe&) = delete;
			NodeProbe(NodeProbe&& other) noexcept
				: m_graph(other.m_graph), m_token(std::move(other.m_token)),
				  m_nodeInfo(std::move(other.m_nodeInfo)), m_modified(other.m_modified),
				  m_exists(other.m_exists)
			{
				other.m_modified = false;
			}
			NodeProbe& operator=(const NodeInfo& info)
			{
				m_nodeInfo = info;
				m_nodeInfo.token = m_token;
				m_modified = true;
				return *this;
			}

			NodeInfo* operator->()
			{
				m_modified = true;
				return &m_nodeInfo;
			}

			const NodeInfo* operator->() const
			{
				return &m_nodeInfo;
			}

			NodeInfo& operator*()
			{
				m_modified = true;
				return m_nodeInfo;
			}

			const NodeInfo& operator*() const
			{
				return m_nodeInfo;
			}

			bool exists() const { return m_exists; }

			const Token& token() const { return m_token; }

			NodeProbe& addPredecessor(const Token& pred)
			{
				auto& preds = m_nodeInfo.predecessors;
				if (std::find(preds.begin(), preds.end(), pred) == preds.end()) {
					preds.push_back(pred);
					m_modified = true;
				}
				return *this;
			}

			NodeProbe& removePredecessor(const Token& pred)
			{
				auto& preds = m_nodeInfo.predecessors;
				auto it = std::find(preds.begin(), preds.end(), pred);
				if (it != preds.end()) {
					preds.erase(it);
					m_modified = true;
				}
				return *this;
			}

			NodeProbe& addSuccessor(const Token& succ)
			{
				auto& succs = m_nodeInfo.successors;
				if (std::find(succs.begin(), succs.end(), succ) == succs.end()) {
					succs.push_back(succ);
					m_modified = true;
				}
				return *this;
			}

			NodeProbe& removeSuccessor(const Token& succ)
			{
				auto& succs = m_nodeInfo.successors;
				auto it = std::find(succs.begin(), succs.end(), succ);
				if (it != succs.end()) {
					succs.erase(it);
					m_modified = true;
				}
				return *this;
			}

		private:
			TokenGraph& m_graph;
			Token m_token;
			NodeInfo m_nodeInfo;
			bool m_modified;
			bool m_exists;
		};
		NodeProbe operator[](Token token)
		{
			return NodeProbe(*this, token);
		}
		std::vector<Value> order() const
		{
			return m_order;
		}
		void updateNode(const NodeInfo& info)
		{
			removeNode(info.token);
			addNode(info);
		}
		std::vector<Value> computeOrder(std::function<bool(const Value&)> canVisit)
		{
			std::deque<BoostVertex> sortedVertices;

			std::map<BoostVertex, std::size_t> vertex_index_map;
			std::size_t index = 0;
			for (auto [v_iter, v_end] = boost::vertices(m_graph); v_iter != v_end; ++v_iter) {
				vertex_index_map[*v_iter] = index++;
			}
			auto index_pmap = boost::make_assoc_property_map(vertex_index_map);

			std::map<BoostVertex, boost::default_color_type> vertex_color_map;
			auto color_pmap = boost::make_assoc_property_map(vertex_color_map);

			boost::topological_sort(m_graph, std::front_inserter(sortedVertices),
								   boost::vertex_index_map(index_pmap).color_map(color_pmap));

			std::vector<Value> ret;

			for (auto vertex : sortedVertices) {
				auto it = m_vertex.right.find(vertex);
				if (it != m_vertex.right.end()) {
					Token token = it->second;
					if (hasNode(token) && canVisit(m_nodeMap[token].value)) {
						ret.push_back(m_nodeMap[token].value);
					}
				}
			}
			return ret;
		}

	public:
		/**
		 * dfs
		 */
		template<typename Visitor>
		class TokenGraphDFSVisitor : public boost::default_dfs_visitor
		{
		private:
			const TokenGraph* graph;
			Visitor visitor;
			mutable std::set<Token> visitedTokens;

		public:
			TokenGraphDFSVisitor(const TokenGraph* g, Visitor v)
				: graph(g), visitor(v) {}

			template<typename VertexDescriptor, typename Graph>
			void discover_vertex(VertexDescriptor v, const Graph& g) const
			{
				auto vertex_token_it = graph->m_vertex.right.find(v);
				if (vertex_token_it != graph->m_vertex.right.end()) {
					Token token = vertex_token_it->second;
					if (graph->hasNode(token) && visitedTokens.find(token) == visitedTokens.end()) {
						visitedTokens.insert(token);
						visitor(graph->m_nodeMap.at(token).value);
					}
				}
			}
		};
	    template<typename Visitor>
	    void visitDFSFromRoots(Visitor visitor) const
		{
			std::vector<BoostVertex> rootVertices;

			for (auto [v_iter, v_end] = boost::vertices(m_graph); v_iter != v_end; ++v_iter) {
				if (boost::in_degree(*v_iter, m_graph) == 0) {
					auto vertex_token_it = m_vertex.right.find(*v_iter);
					if (vertex_token_it != m_vertex.right.end() && hasNode(vertex_token_it->second)) {
						rootVertices.push_back(*v_iter);
					}
				}
			}

			std::map<BoostVertex, boost::default_color_type> vertex_color_map;
			auto color_pmap = boost::make_assoc_property_map(vertex_color_map);

			TokenGraphDFSVisitor<Visitor> dfs_visitor(this, visitor);

			for (BoostVertex root : rootVertices) {
				boost::depth_first_visit(m_graph, root,
					boost::visitor(dfs_visitor).color_map(color_pmap));
			}
		}
		std::vector<Token> getActivePredecessors(const Token& token) const
	    {
	    	std::vector<Token> activePredecessors;

	    	auto token_it = m_vertex.left.find(token);
	    	if (token_it == m_vertex.left.end()) {
	    		return activePredecessors;
	    	}

	    	BoostVertex vertex = token_it->second;

	    	auto [in_edge_iter, in_edge_end] = boost::in_edges(vertex, m_graph);
	    	for (auto edge_iter = in_edge_iter; edge_iter != in_edge_end; ++edge_iter) {
	    		BoostVertex source_vertex = boost::source(*edge_iter, m_graph);

	    		auto vertex_token_it = m_vertex.right.find(source_vertex);
	    		if (vertex_token_it != m_vertex.right.end()) {
	    			Token predecessor_token = vertex_token_it->second;

	    			if (hasNode(predecessor_token)) {
	    				activePredecessors.push_back(predecessor_token);
	    			} else {
	    				auto subPredecessors = getActivePredecessors(predecessor_token);
	    				activePredecessors.insert(activePredecessors.end(), subPredecessors.begin(), subPredecessors.end());
	    			}
	    		}
	    	}

	    	return activePredecessors;
	    }
		        std::vector<Token> getActiveSuccessors(const Token& token) const
        {
        	std::vector<Token> activeSuccessors;

        	auto token_it = m_vertex.left.find(token);
        	if (token_it == m_vertex.left.end()) {
        		return activeSuccessors;
        	}

        	BoostVertex vertex = token_it->second;

        	auto [out_edge_iter, out_edge_end] = boost::out_edges(vertex, m_graph);
        	for (auto edge_iter = out_edge_iter; edge_iter != out_edge_end; ++edge_iter) {
        		BoostVertex target_vertex = boost::target(*edge_iter, m_graph);

        		auto vertex_token_it = m_vertex.right.find(target_vertex);
        		if (vertex_token_it != m_vertex.right.end()) {
        			Token successor_token = vertex_token_it->second;

        			if (hasNode(successor_token)) {
        				activeSuccessors.push_back(successor_token);
        			} else {
        				auto subSuccessors = getActiveSuccessors(successor_token);
        				activeSuccessors.insert(activeSuccessors.end(), subSuccessors.begin(), subSuccessors.end());
        			}
        		}
        	}

        	return activeSuccessors;
        }
	private:
		TokenGraphSavedBoostGraph m_graph;
		boost::bimap<
	    	boost::bimaps::unordered_set_of<Token>,
	    	BoostVertex
		> m_vertex;
		//std::unordered_map<Token,BoostVertex> m_vertex;
		std::unordered_map<Token, NodeInfo> m_nodeMap;
		std::vector<Value> m_order;
	};
}
#endif //TOKENGRAPH_H
