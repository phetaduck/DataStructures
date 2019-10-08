#pragma once

#include <memory>
#include <optional>
#include <functional>


template <class Data, class K = size_t>
struct Key {
	using value_type = K;
	using data_type = Data;
	value_type value {};
	data_type data {};
	operator value_type() const {
		return value;
	}
	operator data_type() const {
		return data;
	}
	bool operator==(const Key& nodeKey) const {
		return value == nodeKey.value;
	}
	bool operator>(const Key& nodeKey) const {
		return value > nodeKey.value;
	}
	bool operator<(const Key& nodeKey) const {
		return value < nodeKey.value;
	}
};

template<class T>
class BSTree {
public:
	using value_type = T;

	BSTree() = default;
	BSTree(const BSTree&) = default;
	BSTree& operator=(const BSTree&) = default;
	BSTree(BSTree&&) = default;
	BSTree& operator=(BSTree&&) = default;
	virtual ~BSTree() = default;

	BSTree(value_type t) {
		_root = Node::make_shared (t);
	}

	template<class Iter>
	BSTree(Iter first, Iter last)
	{
		if (!_root) _root = Node::make_shared (*first++);
		for (auto it = first; it != last; ++it) {
			insert(*it);
		}
	}

	bool insert(value_type t)
	{
		return _root->insert(t);
	}

	template<class Visitor, class ...Args>
	void preorder(const Visitor& visitor, Args&&... args) {
		_root->preorder(visitor, std::forward<Args>(args)...);
	}

	class Node : public std::enable_shared_from_this <Node> {
	public:
		Node() = delete;
		Node(const Node&) = default;
		Node& operator=(const Node&) = default;
		Node(Node&&) = default;
		Node& operator=(Node&&) = default;
		virtual ~Node() = default;

		Node(value_type t) {
			key_ = std::move(t);
		}

		Node(value_type t, std::shared_ptr<Node> parent) {
			key_ = std::move(t);
			this->parent_ = parent;
			this->coord_.y = parent->coord_.y + 1;
		}

		value_type& key() {
			return key_;
		}

		const value_type& key() const {
			return const_cast<Node*>(this)->key_();
		}

		auto coord() const {
			return coord_;
		}

		auto left() const {
			return left_;
		}

		auto right() const {
			return right_;
		}

		auto parent() const {
			return parent_;
		}

		static std::shared_ptr<Node> make_shared(value_type t) {
			auto out = std::make_shared<Node> (t);
			return out;
		}

		static std::shared_ptr<Node> make_shared(value_type t, std::shared_ptr<Node> parent) {
			auto out = std::make_shared<Node> (t, parent);
			return out;
		}

		auto ptr() {
			return this->shared_from_this ();
		}

		auto w_ptr() {
			return this->weak_from_this ();
		}

		bool insert(value_type t)
		{
			if (key_ == t) return false;
			if (key_ > t) {
				if (right_) return right_->insert(t);
				else {
					right_ = make_shared (t, ptr());
					right_->coord_.x = coord_.x + 1;
					return true;
				}
			}
			if (key_ < t) {
				if (left_) return left_->insert(t);
				else {
					left_ = make_shared (t, ptr());
					left_->coord_.x = coord_.x - 1;
					return true;
				}
			}
			key_ = std::move(t);
			return true;
		}

		template<class Visitor, class ...Args>
		void preorder(const Visitor& visitor, Args&&... args) {
			visitor(ptr (), std::forward<Args>(args)...);
			if (left_) left_->preorder(visitor, std::forward<Args>(args)...);
			if (right_) right_->preorder(visitor, std::forward<Args>(args)...);
		}

		struct Point {
			int x = 0;
			int y = 0;
		};

	private:
		value_type key_;
		/*useful for visual representation.*/
		/*y < 0 == left side, y > 0 == right, root == 0*/
		Point coord_;
		std::shared_ptr<Node> left_;
		std::shared_ptr<Node> right_;
		std::weak_ptr<Node> parent_;
	};
	using node_type = std::shared_ptr<Node>;

private:
	node_type _root;
};

template <class Iter>
BSTree(Iter first, Iter last) -> BSTree<typename std::iterator_traits<Iter>::value_type>;
