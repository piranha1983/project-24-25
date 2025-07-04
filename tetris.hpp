#include <iostream>
#include <cassert>
#include <cstdint>

struct tetris_exception {
    tetris_exception(std::string const& str) : m_str(str) {}
    std::string what() const { return m_str; }

private:
    std::string m_str;
};

struct piece {
    piece();  // done
    piece(uint32_t s, uint8_t c);  // done
    piece(piece const& rhs);  // done
    piece(piece&& rhs);  // done
    ~piece();  // done

    piece& operator=(piece const& rhs);  // done
    piece& operator=(piece&& rhs);  // done

    bool operator==(piece const& rhs) const;  // done
    bool operator!=(piece const& rhs) const;  // done

    bool& operator()(uint32_t i, uint32_t j);  // done
    bool operator()(uint32_t i, uint32_t j) const;  // done

    bool empty(uint32_t i, uint32_t j, uint32_t s) const;  // done
    bool full(uint32_t i, uint32_t j, uint32_t s) const;  // done
    bool empty() const;  // done
    bool full() const;  // done

    void rotate();  // done
    void cut_row(uint32_t i);  // done
    void print_ascii_art(std::ostream& os) const;

    uint32_t side() const;  // done
    int color() const;  // done

private:
    uint32_t m_side;
    uint8_t m_color;
    bool** m_grid;
};

std::istream& operator>>(std::istream& is, piece& p);
std::ostream& operator<<(std::ostream& os, piece const& p);

struct tetris_piece {
    piece p;
    int x;
    int y;
};

class tetris  //
{
    struct node {
        tetris_piece tp;
        node* next;
    };

public:
    tetris();
    tetris(uint32_t w, uint32_t h, uint32_t s = 0);
    tetris(tetris const& rhs);
    tetris(tetris&& rhs);
    ~tetris();

    tetris& operator=(tetris const& rhs);
    tetris& operator=(tetris&& rhs);

    bool operator==(tetris const& rhs) const;
    bool operator!=(tetris const& rhs) const;

    void insert(piece const& p, int x);
    void add(piece const& p, int x, int y);

    bool containment(piece const& p, int x, int y) const;

    void print_ascii_art(std::ostream& os) const;

    struct iterator {
        using iterator_category = std::forward_iterator_tag;
        using value_type = tetris_piece;
        using reference = tetris_piece&;
        using pointer = tetris_piece*;

        iterator(node* ptr);
        reference operator*();
        pointer operator->();
        iterator& operator++();
        iterator operator++(int /*dummy*/);
        bool operator==(iterator const& rhs) const;
        bool operator!=(iterator const& rhs) const;

    private:
        node* m_ptr;
    };

    struct const_iterator {
        using iterator_category = std::forward_iterator_tag;
        using value_type = tetris_piece const;
        using reference = tetris_piece const&;
        using pointer = tetris_piece const*;

        const_iterator(node const* ptr);
        reference operator*() const;
        pointer operator->() const;
        const_iterator& operator++();
        const_iterator operator++(int /*dummy*/);
        bool operator==(const_iterator const& rhs) const;
        bool operator!=(const_iterator const& rhs) const;

    private:
        node const* m_ptr;
    };

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    uint32_t score() const;
    uint32_t width() const;
    uint32_t height() const;

private:
    uint32_t m_score;
    uint32_t m_width;
    uint32_t m_height;
    node* m_field;
};

std::ostream& operator<<(std::ostream& os, tetris const& t);
std::istream& operator>>(std::istream& is, tetris& t);


