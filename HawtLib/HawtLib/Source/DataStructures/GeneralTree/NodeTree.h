#pragma once

#include <vector>
#include <optional>
#include <functional>
#include <map>
#include <iostream>

namespace HawtLib {
	namespace DataStructures {

		template <typename T> class NodeTree;

		template <typename T> struct Node {
			std::optional<T> data;

		private:
			std::vector<Node<T>*> children;
			Node<T>* parent;
			friend class NodeTree<T>;
		};

		template <typename T> class NodeTree {
		public:


		private:
			size_t id;
			size_t m_Size;
			std::map<size_t, Node<T>*> m_NodeMemoryMap;
			Node<T>* m_Root;
			Node<T>* m_Head;

		public:

			NodeTree() : id(0), m_Size(1) {
				m_Root = new Node<T>;
				m_Root->parent = nullptr;
				m_Head = m_Root;
			}

			~NodeTree() {
				Clean(m_Root);
			}

		public:

			Node<T>& GetRoot() {
				return *m_Root;
			}

			Node<T>& GetHead() {
				return *m_Head;
			}

			std::vector<Node<T>*>& GetChildren() {
				return m_Head->children;
			}

			size_t GetChildrenCount() {
				return m_Head->children.size();
			}

			Node<T>& GetNodeFromId(size_t id) {
				return *m_NodeMemoryMap[id];
			}

			std::optional<T> GetData(size_t id) const {
				return m_NodeMemoryMap.at(id)->data;
			}

			std::optional<T> GetData(Node<T>* node) const {
				return node->data;
			}

			std::optional<T> GetData() const {
				return m_Head->data;
			}

		public:
			void MoveHeadParent() {
				if (m_Head != nullptr) {
					m_Head = m_Head->parent;
				}
			}

			void MoveHeadChild(size_t idx) {
				if (idx < m_Head->children.size()) {
					m_Head = m_Head->children[idx];
				}
			}

			void MoveHeadToId(size_t id) {
				m_Head = m_NodeMemoryMap[id];
			}

		public:
			size_t AddNode(std::optional<T> data = std::nullopt) {
				auto newNode = new Node<T>;
				newNode->data = data;
				newNode->parent = m_Head;
				m_Head->children.push_back(newNode);
				++m_Size;
				++id;
				m_NodeMemoryMap[id] = newNode;
				return id;
			}

			void RemoveNode(size_t id) {	// remove from the id
				Node<T>* removeNode = m_NodeMemoryMap[id];
				Node<T>* parentNode = removeNode->parent;	// ptr
				std::vector<Node<T>*> childrenNodes = removeNode->children;	//copy
				delete removeNode;
				parentNode->children.insert(parentNode->children.end(), childrenNodes.begin(), childrenNodes.end());
				--m_Size;
			}

			void RemoveNode(Node<T>* removeNode) {	// remove node
				//Node<T>* removeNode = node;
				Node<T>* parentNode = removeNode->parent;	// ptr
				std::vector<Node<T>*> childrenNodes = removeNode->children;	//copy
				delete removeNode;
				parentNode->children.insert(parentNode->children.end(), childrenNodes.begin(), childrenNodes.end());
				--m_Size;
			}

			void RemoveNode() {	// remove current head
				Node<T>* toDelete = m_Head;										// save curretn head's mem address as toDelete						
				Node<T>* pParentNode = toDelete->parent;						// save current head parent
				std::vector<Node<T>*> childrenNodes = toDelete->children;		// save curretn head children
				m_Head = pParentNode;											// set head to parent
				m_Head->children.insert(m_Head->children.end(), childrenNodes.begin(), childrenNodes.end());	// append former children of former head to new head
				delete toDelete;
				--m_Size;
			}

		public:
			void SetData(size_t id, std::optional<T> data) {
				m_NodeMemoryMap[id]->data = data;
			}

			void SetData(Node<T>* node, std::optional<T> data) {
				node->data = data;
			}

			void SetData(std::optional<T> data) {
				m_Head->data = data;
			}

		public:
			void Clean(Node<T>* startNode) {
				TraverseFromBottom(startNode, [](Node<T>* node) {
					delete node;
					});
			}

			void Clean(size_t id) {
				TraverseFromBottom(m_NodeMemoryMap[id], [](Node<T>* node) {
					delete node;
					});
			}

			void Clean() {	// clean from head
				TraverseFromBottom(m_Head, [](Node<T>* node) {
					delete node;
					});
			}

		public:
			void TraverseFromTop(size_t id, std::function<void(Node<T>*)> func) {
				_TraverseFromTop(m_NodeMemoryMap.at(id), func);
			}

			void TraverseFromTop(std::function<void(Node<T>*)> func) {
				_TraverseFromTop(m_Head, func);
			}

			void TraverseFromBottom(size_t id, std::function<void(Node<T>*)> func) {
				_TraverseFromBottom(m_NodeMemoryMap.at(id), func);
			}

			void TraverseFromBottom(std::function<void(Node<T>*)> func) {
				_TraverseFromBottom(m_Head, func);
			}

		private:

			void _TraverseFromTop(Node<T>* traverseNode, std::function<void(Node<T>*)> func, Node<T>* endNode = nullptr) {
				if (traverseNode->children.empty()) return;
				for (size_t i = 0; i < traverseNode->children.size(); ++i) {
					if (traverseNode->children[i] == endNode) return;
					func(traverseNode->children[i]);
					if (i == traverseNode->children.size() - 1) {
						for (Node<T>* node : traverseNode->children) {
							_TraverseFromTop(node, func);
						}
					}
				}
			}

			void _TraverseFromBottom(Node<T>* startNode, std::function<void(Node<T>*)> func, Node<T>* endNode = nullptr) {

				for (Node<T>* node : startNode->children) {
					_TraverseFromBottom(node, func);
					func(node);
				}
			}


		};
	}
}