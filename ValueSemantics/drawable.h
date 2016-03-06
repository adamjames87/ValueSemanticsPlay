#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include <ostream>
#include <string>

template <typename T>
void draw(const T& x, std::ostream& out, size_t position)
{
 out << std::string(position, ' ') << x <<  std::endl;
}


class object_t {
   public:
      template <typename T>
      object_t(const T& x) : self_(new model<T>(std::move(x))) { std::cout << "ctor" << std::endl;};

      object_t(const object_t& other) : self_(other.self_->copy_()) { std::cout << "copy" << std::endl;};

      object_t& operator=(const object_t& other) noexcept
      {
         object_t tmp(other);
         *this = std::move(tmp);
         return *this;
      }

      // move constructor
      object_t(object_t&& other) noexcept = default;

      // move assignment
      object_t& operator=(object_t&& other) noexcept = default;


      friend void draw(const object_t& x, std::ostream& out, size_t position)
      {
      x.self_->draw_(out, position);
      }

   private:
      struct concept_t {
         virtual ~concept_t() = default;
         virtual concept_t* copy_() const = 0;
         virtual void draw_(std::ostream& out, size_t position) const = 0;
      };

      template<typename T>
      struct model : concept_t {
         model(T x) : data_(std::move(x)) {}
         concept_t* copy_() const {return new model(*this); }
         void draw_(std::ostream& out, size_t position) const {
            draw(data_, out, position);
         }

         T data_;
      };


   std::unique_ptr<concept_t> self_;
};


using document_t = std::vector<object_t>;

// Draw the document.
void draw(const document_t& doc, std::ostream& out, size_t position)
{
   out << std::string(position, ' ') << "<Document>" << std::endl;
   for (const auto& e: doc)
      {
      draw(e, out, position + 4);
      }
   out << std::string(position, ' ') << "</Document>" << std::endl;
}

using history_t = std::vector<document_t>;

// commit = push the back onto the end
void commit(history_t& h) {h.push_back(h.back()); }
void undo(history_t& h) {h.pop_back(); }
document_t& current(history_t& h) {return h.back(); }

