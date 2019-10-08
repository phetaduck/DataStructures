#pragma once

#include <memory>
#include <optional>
#include <functional>


template<class T>
class BSTree {
public:
	BSTree() = delete;
	BSTree(const BSTree&) = default;
	BSTree& operator=(const BSTree&) = default;
	BSTree(BSTree&&) = default;
	BSTree& operator=(BSTree&&) = default;
	virtual ~BSTree() = default;

	BSTree(T t) {
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

	bool insert(T t)
	{
		return _root->insert(t);
	}

	template<class Visitor, class ...Args>
	void preorder(const Visitor& visitor, Args&&... args) {
		_root->preorder(visitor, std::forward<Args>(args)...);
	}

	struct Point {
		int x = 0;
		int y = 0;
	};

	class Node : public std::enable_shared_from_this <Node> {
	public:
		Node() = delete;
		Node(const Node&) = default;
		Node& operator=(const Node&) = default;
		Node(Node&&) = default;
		Node& operator=(Node&&) = default;
		virtual ~Node() = default;

		Node(T t) {
			key_ = std::move(t);
		}

		Node(T t, std::shared_ptr<Node> parent) {
			key_ = std::move(t);
			this->parent_ = parent;
			this->coord_.y = parent->coord_.y + 1;
		}

		T& key() {
			return key_;
		}

		const T& key() const {
			return const_cast<Node*>(this)->key_();
		}

		auto coord() {
			return coord_;
		}

		auto left() {
			return left_;
		}

		auto right() {
			return right_;
		}

		auto parent() {
			return parent_;
		}

		static std::shared_ptr<Node> make_shared(T t) {
			auto out = std::make_shared<Node> (t);
			return out;
		}

		static std::shared_ptr<Node> make_shared(T t, std::shared_ptr<Node> parent) {
			auto out = std::make_shared<Node> (t, parent);
			return out;
		}

		auto ptr() {
			return this->shared_from_this ();
		}

		auto w_ptr() {
			return this->weak_from_this ();
		}

		bool insert(T t)
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
	private:
		T key_;
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
