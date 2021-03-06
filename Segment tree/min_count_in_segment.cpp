#include <iostream>
#include <vector>

typedef long long int ln;

using namespace std;

class seg_tree {
private :
    ln size;
    vector<pair<ln, ln>> segment;

    // API (update)
    pair<ln, ln> find_pair(pair<ln, ln>& x, pair<ln, ln>& y) {
        if(x.first > y.first) {
            return y;
        } 
        else if(x.first < y.first) {
            return x;
        }
        return make_pair(x.first, x.second + y.second);
    }

    void set(ln index, ln val, ln l, ln r, ln in) {
        if(l - r == 0) {
            segment[in] = {val, 1};
            return;
        }

        ln mid = l - (l - r) / 2;

        if(mid >= index)
            set(index, val, l, mid, in*2 + 1);
        else
            set(index, val, mid + 1, r, in*2 + 2);

        segment[in] = find_pair(segment[in*2 + 1], segment[in*2 + 2]);
        return;
    }

    pair<ln, ln> countMin(ln l, ln r, ln lx, ln ry, ln index) {
        if(l > ry || r < lx)    return {INT32_MAX, 0};

        if(lx >= l && ry <= r)  return segment[index];

        pair<ln, ln> s1, s2;
        
        ln mid = lx - (lx - ry) / 2;

        s1 = countMin(l, r, lx, mid, index*2 + 1);
        s2 = countMin(l, r, mid + 1, ry, index*2 + 2);

        return find_pair(s1, s2);
    }

    void build(vector<ln>& vec, ln index, ln l, ln r, ln size) {

        if(l - r == 0) {
            if(size > l)
                segment[index] = make_pair(vec[l], 1);
            return;
        }

        ln mid = l - (l - r) / 2;

        build(vec, index*2 + 1, l, mid, size);
        build(vec, index*2 + 2, mid + 1, r, size);

        segment[index] = find_pair(segment[index*2 + 1], segment[index*2 + 2]);
        return;
    }   

    // void traverse(ln index) {

    //     if(index >= size*2 - 1) return ;

    //     cout << segment[index] << " ";

    //     traverse(index*2 + 1);
    //     traverse(index*2 + 2);

    //     return ;
    // }

public :
    seg_tree(ln N) {
        size = 1;
        while(size < N) size *= 2;

        segment.assign(size*2 - 1, {0, 0});
    }    
    void build(vector<ln>& vec) {
        build(vec, 0, 0, size - 1, vec.size());
    }
    pair<ln, ln> countMin(ln l, ln r) {
        return countMin(l, r, 0, size - 1, 0);
    }
    void set(ln index, ln val) {
        set(index, val, 0, size - 1, 0);
    }
    
    // void traverse() {
    //     traverse(0);
    // }
};

int main() {

    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); 

    ln N, M;
    cin >> N >> M;
    vector<ln> vec(N); 

    seg_tree tree(N);


    for(ln i = 0; i < N; ++i) {
        ln in;
        cin >> in;
        vec[i] = in;
    }

    tree.build(vec);

    while(M--) {
        ln in;
        cin >> in;

        if(in == 1) {
            ln i, v;
            cin >> i >> v;

            tree.set(i, v);
        } else {
            ln l, r;
            cin >> l >> r;
            auto result = tree.countMin(l, r - 1);
            cout << result.first << " " << result.second << "\n";
        }
    }
    
    //tree.traverse();
    return 0;
}