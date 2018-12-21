#pragma once
//#include "SmallList.hpp"
#include <vector>

template<typename T>
using SmallList = std::vector<T>;

template <class T>
class FreeList
{
public:
    /// Creates a new free list.
    FreeList();

    /// Inserts an element to the free list and returns an index to it.
    int insert(const T& element);

    // Removes the nth element from the free list.
    void erase(int n);

    // Removes all elements from the free list.
    void clear();

    // Returns the range of valid indices.
    int range() const;

    void reserve(int size)
    {
        data.reserve(size);
    }

    // Returns the nth element.
    T& operator[](int n);

    // Returns the nth element.
    const T& operator[](int n) const;

private:
    union FreeElement
    {
        T element;
        int next;
    };
    std::vector<FreeElement> data;
    int first_free;
};

template <class T>
FreeList<T>::FreeList(): first_free(-1)
{
}

template <class T>
int FreeList<T>::insert(const T& element)
{
    if (first_free != -1)
    {
        const int index = first_free;
        first_free = data[first_free].next;
        data[index].element = element;
        return index;
    }
    else
    {
        FreeElement fe;
        fe.element = element;
        data.push_back(fe);
        return static_cast<int>(data.size() - 1);
    }
}

template <class T>
void FreeList<T>::erase(int n)
{
    data[n].next = first_free;
    first_free = n;
}

template <class T>
void FreeList<T>::clear()
{
    data.clear();
    first_free = -1;
}

template <class T>
int FreeList<T>::range() const
{
    return static_cast<int>(data.size());
}

template <class T>
T& FreeList<T>::operator[](int n)
{
    return data[n].element;
}

template <class T>
const T& FreeList<T>::operator[](int n) const
{
    return data[n].element;
}

struct LGridElt
{
    // Stores the index to the next element in the cell using an indexed SLL.
    int next;

    // Stores the ID of the element. This can be used to associate external
    // data to the element.
    int id;

    // Stores the center of the element.
    float mx, my;

    // Stores the half-size of the element relative to the upper-left corner
    // of the grid.
    float hx, hy;
};

struct LGridLooseCell
{
    // Stores the index to the first element using an indexed SLL.
    int head;

    // Stores the extents of the grid cell relative to the upper-left corner
    // of the grid which expands and shrinks with the elements inserted and
    // removed.
    float l, t, r, b;
};

struct LGridTightCell
{
    // Stores the index to the next loose cell in the grid cell.
    int next;

    // Stores the position of the loose cell in the grid.
    int loose_x, loose_y;
};

struct LGridRow
{
    // Stores all the elements in the row.
    FreeList<LGridElt> elts;

    // Stores all the loose cells in the row.
    LGridLooseCell* lcells;

    // Stores the number of elements in the row.
    int num_elts;
};

struct LGrid
{
    // Stores all the tight cell nodes in the grid.
    FreeList<LGridTightCell> tcells;

    // Stores all the rows in the grid.
    LGridRow* rows;

    // Stores the tight cell heads.
    int* tcell_heads;

    // Stores the number of columns in the grid.
    int num_cols;

    // Stores the number of rows in the grid.
    int num_rows;

    // Stores the size of a cell.
    float cell_w, cell_h;

    // Stores the inverse size of a cell.
    float inv_cell_w, inv_cell_h;

    // Stores the upper-left corner of the grid.
    float x, y;

    // Stores the size of the grid.
    float w, h;
};

// Creates a loose grid encompassing the specified extents using the specified cell
// size. Elements inserted to the loose grid are only inserted in one cell, but the
// extents of each cell are allowed to expand and shrink. To avoid requiring every
// loose cell to be checked during a search, a second grid of tight cells referencing
// the loose cells is stored.
LGrid* lgrid_create(float cell_w, float cell_h, float l, float t, float r, float b);

// Destroys the grid.
void lgrid_destroy(LGrid* grid);

// Returns the grid X position for the specified free X position.
int lgrid_cell_x(LGrid* grid, float x);

// Returns the grid Y position for the specified free Y position.
int lgrid_cell_y(LGrid* grid, float y);

// Inserts an element to the grid.
void lgrid_insert(LGrid* grid, int id, float mx, float my, float hx, float hy);

// Removes an element from the grid.
void lgrid_remove(LGrid* grid, int id, float mx, float my);

// Moves an element in the grid from the former position to the new one.
void lgrid_move(LGrid* grid, int id, float prev_mx, float prev_my, float mx, float my);

// Moves an element in the grid from the former position to the new one in the
// same cell. Note that the new element position should belong in the same cell
// as the former one.
void lgrid_move_cell(LGrid* grid, int id, int cell_x, int cell_y, float mx, float my);

// Returns all the elements that intersect the specified rectangle excluding elements
// with the specified ID to omit.
SmallList<int> lgrid_query(const LGrid* grid, float mx, float my, float hx, float hy, int omit_id);

// Returns true if the specified rectangle is inside the grid boundaries.
bool lgrid_in_bounds(const LGrid* grid, float mx, float my, float hx, float hy);

// Optimizes the grid, shrinking bounding boxes in response to removed elements and
// rearranging the memory of the grid to allow cache-friendly cell access.
void lgrid_optimize(LGrid* grid);
