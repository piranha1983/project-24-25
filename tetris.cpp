#include "tetris.hpp"

/* Your implementation goes here! */

piece::piece() : m_side(0), m_color(0), m_grid(nullptr) {}


bool isPowerOfTwo(int n) {
    if (n <= 0) return false;
    while (n % 2 == 0) {
        n /= 2;
    }
    return n == 1;
}


piece::piece(uint32_t s, uint8_t c) : m_side(s), m_color(c) {
    if(!isPowerOfTwo(s))
        throw tetris_exception("Piece side must be a power of two");
    if(c == 0)
        throw tetris_exception("Piece color must be from 1 to 255");

    m_grid = new bool*[m_side];
    for(uint32_t i = 0; i < m_side; ++i) {
        m_grid[i] = new bool[m_side]();
    }
}


piece::piece(piece const& rhs) : m_side(rhs.m_side), m_color(rhs.m_color) {
    m_grid = new bool*[m_side];

    for(uint32_t i = 0; i<m_side; i++) {
        m_grid[i] = new bool[m_side];
        for(uint32_t j = 0; j < m_side; j++) {
            m_grid[i][j] = rhs.m_grid[i][j];
        }
    }
}


piece::piece(piece&& rhs) : m_side(rhs.m_side), m_color(rhs.m_color), m_grid(rhs.m_grid) {
    rhs.m_side = 0;
    rhs.m_color = 0;
    rhs.m_grid = nullptr;
}


piece::~piece() {
    if(m_grid) {
        for(uint32_t i = 0; i<m_side; i++) 
            delete[] m_grid[i];
        delete[] m_grid;
    }
}


piece& piece::operator=(piece const& rhs) {
    if(this != &rhs) {
        if(m_grid) {
            for(uint32_t i = 0; i < m_side; i++)
                delete[] m_grid[i];
            delete[] m_grid;
        }

        m_side = rhs.m_side;
        m_color = rhs.m_color;

        m_grid = new bool*[m_side];
        for(uint32_t i = 0; i < m_side; ++i) {
            m_grid[i] = new bool[m_side];
            for(uint32_t j = 0; j < m_side; ++j) {
                m_grid[i][j] = rhs.m_grid[i][j];
            }
        }
    }

    return *this;
}


piece& piece::operator=(piece&& rhs) {
    if(this != &rhs) {
        if(m_grid) {
            for(uint32_t i = 0; i < m_side; i++)
                delete[] m_grid[i];
            delete[] m_grid;
        }

        m_side = rhs.m_side;
        m_color = rhs.m_color;
        m_grid = rhs.m_grid;
        rhs.m_side = 0;
        rhs.m_color = 0;
        rhs.m_grid = nullptr;
    }

    return *this;
}


bool piece::operator==(piece const& rhs) const {
    if(m_side != rhs.m_side || m_color != rhs.m_color)
        return false;
    
    for(uint32_t i=0; i<m_side; ++i) {
        for(uint32_t j=0; j<m_side; ++j) {
            if(m_grid[i][j] != rhs.m_grid[i][j]) {
                return false;
            }
        }
    }

    return true;
}


bool piece::operator!=(piece const& rhs) const {
    return !(*this == rhs);
}


bool& piece::operator()(uint32_t i, uint32_t j) {
    if(i >= m_side || j >= m_side) {
        throw tetris_exception("Index out of bounds");
    }
    return m_grid[i][j];
}


bool piece::operator()(uint32_t i, uint32_t j) const {
    if(i >= m_side || j >= m_side) {
        throw tetris_exception("Index out of bounds");
    }
    return m_grid[i][j];
}


bool piece::empty(uint32_t i, uint32_t j, uint32_t s) const {
    if(i + s > m_side || j + s > m_side)
        throw tetris_exception("Square out of bounds");
    
    bool is_empty = true;
    for(uint32_t l=i; l<i+s && is_empty; l++) {
        for(uint32_t k=j; k<j+s && is_empty; k++) {
            if(m_grid[l][k])
                is_empty = false;
        }
    }
    
    return is_empty;
}


bool piece::full(uint32_t i, uint32_t j, uint32_t s) const {
    if(i + s > m_side || j + s > m_side)
        throw tetris_exception("Square out of bounds");

    bool is_full = true;
    for(uint32_t l=i; l<i+s && is_full; l++) {
        for(uint32_t k=j; k<j+s && is_full; k++) {
            if(!m_grid[l][k])
                is_full = false;
        }
    }
    
    return is_full;
}


bool piece::empty() const {
    if(m_side == 0) 
        return true;

    bool is_empty = true;
    for(uint32_t i = 0; i < m_side && is_empty; ++i) {
        for(uint32_t j = 0; j < m_side && is_empty; ++j) {
            if(m_grid[i][j]) {
                is_empty = false;
            }
        }
    }
    return is_empty;
}
        

bool piece::full() const {
    if(m_side > 0) {

        bool is_full = true;
        for(uint32_t i = 0; i < m_side && is_full; ++i) {
            for(uint32_t j = 0; j < m_side && is_full; ++j) {
                if(!m_grid[i][j]) {
                    is_full = false;
                }
            }
        }
        return is_full;
    }

    return false;
}


void piece::rotate() {
    piece support = *this;
    for(uint32_t i=0; i<m_side; i++) {
        for(uint32_t j=0; j<m_side; j++) {
            m_grid[i][j] = support.m_grid[j][support.m_side-i-1];
        }
    }
}


void piece::cut_row(uint32_t i) {
    if(i >= m_side) 
        throw tetris_exception("Index out of bound");

    for(uint32_t l=i; l>0; l--) {
        for(uint32_t j=0; j<m_side; j++) {
            m_grid[l][j] = m_grid[l-1][j];
        }
    }

    for(uint32_t j = 0; j < m_side; ++j) {
        m_grid[0][j] = false;
    }
}


// per debug
void piece::print_ascii_art(std::ostream& os) const {
    if(m_side == 0) {
        os << "Empty piece\n";
        return;
    }

    for(uint32_t i = 0; i < m_side; ++i) {
        for(uint32_t j = 0; j < m_side; ++j) {
            if(m_grid[i][j]) {
                os << static_cast<char>(m_color);
            } else {
                os << '.';
            }
        }
        os << '\n';
    }
}


uint32_t piece::side() const {
    return m_side;
}


int piece::color() const {
    return m_color;
}


void skip_blank_spaces(std::istream& is) {
    char c = 0;
    is >> c;
    is.putback(c);
}


/*
Context-free grammar:
    () -> FULL QUADRANT
    [] -> EMPTY QUADRANT
    (TL TR BL BR) -> RECURSION
*/


std::istream& operator>>(std::istream& is, piece& p) {
    p = PIECE(is);
    return is;
}


void fill(piece& p, uint32_t i, uint32_t j, uint32_t s, bool v) {
    for(uint32_t l = i; l < i + s; ++l)
        for(uint32_t k = j; k < j + s; ++k)
            p(l, k) = v;
}


piece PIECE(std::istream& is) {
    skip_blank_spaces(is);

    uint32_t side;
    uint8_t color;
    is >> side >> color;

    if(!isPowerOfTwo(side))
        throw tetris_exception("Piece side must be a power of two");
    if(color < 1 || color > 255)
        throw tetris_exception("Piece color must be from 1 to 255");

    piece support{side, color};

    skip_blank_spaces(is);
    char c = is.peek();

    if(c == '(') {
        is.get();
        skip_blank_spaces(is);
        c = is.peek();
        if(c == ')') {
            is.get();
            fill(support, 0, 0, side, true);
            return support;
        }
        else {

        }
    }
    else if(c == '[') {
        is.get();
        skip_blank_spaces(is);
        c = is.peek();
        if(c == ']') {
            is.get();
            fill(support, 0, 0, side, false);
            return support;
        }
        else {
            
        }
    }

    for(uint32_t i=0; i<side; i++) {
        for(uint32_t j=0; j<side; j++) {
            switch(c) {
                case '(': {
                    break;
                }
                case '[': {
                    break;
                }
            }
        }
    }
    

    return support;
}


piece FULL(std::istream& is) {
    skip_blank_spaces(is);
}


piece EMPTY(std::istream is) {
    skip_blank_spaces(is);
}
