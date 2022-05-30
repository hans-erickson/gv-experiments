//
//  MIT License
//  
//  Copyright (c) 2021 Hans Erickson
//  
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//  
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//  

#if !defined(GV_OBJECT_H)
#define GV_OBJECT_H

#include <memory>
#include <ranges>
#include <string>
#include <vector>
#include <utility>

// Assumptions:
//   objects are created by graphs
//   edges are created by objects
//   a pointer to a object is stored in the implementation
//   the implementation is derived from Agrec_t and created
//     by agbindrec(), which will be associated with the Agobject_t
//   objects are removed by graphs
//   edges are removed by objects
//   facade container classes are provided for object/edge iteration
//
// object order of creation:
//   1. Agobject_t is created first (by graph)
//   2. object is created (by graph)
//   3. impl_t for object is created by object using agbindrec()
//      The impl_t contains a pointer back to the object
//   4. callbacks are registered for the object that will be called
//      when edges are added or removed, or when the object itself
//      is destroyed


namespace gv
{
    class graph;

    class object
    {
    private:
        struct impl_t;
        std::shared_ptr<impl_t> impl_;

    protected:
        template<typename T>
        class forward_iterator final
        {
        public:
            using difference_type = std::ptrdiff_t;
            using value_type      = T;

            struct constructor_arg_t;

            // Rule of five members
            forward_iterator(const forward_iterator& other);
            forward_iterator(forward_iterator&& other);
            ~forward_iterator();
            forward_iterator& operator=(const forward_iterator& other);
            forward_iterator& operator=(forward_iterator&& other);

            forward_iterator() = default;
            forward_iterator(const constructor_arg_t& arg);
            forward_iterator& operator++();
            forward_iterator operator++(int);
            T& operator*();
            T& operator*() const;
            bool operator==(const forward_iterator& other) const;
            bool operator==(std::default_sentinel_t) const;

        private:
            struct impl_t;
            std::unique_ptr<impl_t> impl_;
        };

        template<typename T>
        class bidirectional_iterator final
        {
        public:
            using difference_type = std::ptrdiff_t;
            using value_type      = T;

            struct constructor_arg_t;

            // Rule of five members
            bidirectional_iterator(const bidirectional_iterator& other);
            bidirectional_iterator(bidirectional_iterator&& other);
            ~bidirectional_iterator();
            bidirectional_iterator& operator=(const bidirectional_iterator& other);
            bidirectional_iterator& operator=(bidirectional_iterator&& other);

            bidirectional_iterator();
            bidirectional_iterator(const constructor_arg_t& arg);
            bidirectional_iterator& operator++();
            bidirectional_iterator& operator--();
            bidirectional_iterator operator++(int);
            bidirectional_iterator operator--(int);
            T& operator*();
            T& operator*() const;
            bool operator==(const bidirectional_iterator& other) const;
            bool operator==(std::default_sentinel_t) const;

        private:
            struct impl_t;
            std::unique_ptr<impl_t> impl_;
        };

        template<typename Iterator>
        requires (std::forward_iterator<Iterator> || std::bidirectional_iterator<Iterator>)
        class view
            : public std::ranges::view_interface<view<Iterator>>
        {
        public:
            view(Iterator i)
                : i_(i)
            {
            }

            Iterator begin() const { return i_; }

            std::default_sentinel_t end() const { return std::default_sentinel; }

        private:
            Iterator i_;
        };

        struct constructor_arg_t;

        object(const constructor_arg_t& arg);

        ~object();

        template<typename T> requires std::derived_from<T, object>
        struct native_pointer_traits;

        template<typename T> requires std::derived_from<T, object>
        static auto
        get_native_ptr(T* ptr)
        {
            using pointer_type = typename native_pointer_traits<T>::pointer_type;
            return reinterpret_cast<pointer_type>(ptr->impl_.get());
        }

        template<typename T> requires std::derived_from<T, object>
        static auto
        get_native_ptr(const T* t)
        {
            return get_native_ptr(const_cast<T*>(t));
        }
        
    public:
        class attribute
        {
        public:
            attribute() = default;

            attribute(const constructor_arg_t& arg);

            std::string
            name();

            std::string
            value();

        private:
            impl_t* ptr_ { nullptr };
        };

        using attribute_iterator = forward_iterator<attribute>;
        using attribute_view     = view<attribute_iterator>;

        enum class kind_t
        {
            graph,
            node,
            edge
        };

        using id_t = int;

        std::string
        get(const std::string& key) const;
        
        attribute_view
        get_attributes() const;

        graph
        graph_of() const;

        kind_t
        kind() const;

        std::string
        name() const;

        graph
        root() const;

        void
        set(const std::string& key, const std::string& value);

    };
}

#endif // GV_OBJECT_H
