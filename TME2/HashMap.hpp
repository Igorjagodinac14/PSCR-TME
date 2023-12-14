#include <iostream>
#include <vector>
#include <string>
#include <forward_list>
using namespace std;

namespace pr {
template <typename K, typename V>
class HashMap{
    public :
    struct Entry{
        K key;
        V value;
    };
    vector<forward_list<Entry>> buckets;

    HashMap(size_t alloc) : buckets(alloc){}

    bool put(K key,V value){
        size_t h = std::hash<K>()(key);
        size_t target = h % buckets.size();
        Entry entry;
        entry.key = key;
        entry.value = value;
        buckets[target].push_front(entry);
        return true;
    }

    int size(){
        int i = 0;
        for (auto & listHP : buckets){
			for (auto & key_hp : listHP){
				i++;
			}
		}
        return i;
    }
    
    class iterator {
        vector<forward_list<Entry>> bucket;
        size_t vit;
        typename forward_list<Entry>::iterator lit;

        iterator(vector<forward_list<Entry>> & bucket,size_t vit,typename forward_list<Entry>::iterator lit): bucket(bucket), lit(lit), bucket(bucket) {}

        iterator& operator++(){
            lit++;
            if (lit == bucket[vit].end()){
                ++vit;
                auto index = vit;
                for (; vit < bucket.size() && bucket[vit].empty(); ++vit){
                    if (buckets[index].empty()){
                        vit = index;
                        lit = bucket[index].begin();
                        return lit;
                    }
                }
                if (vit < bucket.size()){
                    lit = bucket[vit].begin();
                }
            }
            return *this; 
        }
        Entry& operator*(){
            return *lit;
        }

        bool operator!=( const iterator& other){
            return vit != other.vit || lit != other.lit || bucket != other.bucket;lit != other;
        } 
    };
    iterator end(){
        return iterator(buckets.size(),buckets[0].end(),buckets);
    }
    iterator begin(){
        for(size_t index = 0 ; index < buckets.size() ; ++index){
            if (! buckets[index].empty()){
                return iterator(buckets, index, buckets[index].begin());
            }
        }
        return end(); 
    }
    size_t count( iterator begin, iterator end){
        size_t result = 0;
        for (auto it = begin; it != end; ++it ){
            ++result;
        }
        return result;
    }
    template <typename T, typename iterator>
    size_t count_if_equal( iterator begin, iterator end, const T& val){
        size_t result = 0;
        for (auto it = begin; it != end; ++it ){
            if (*it == val){++result;}
        }
        return result;
    }
    /*lors de la compil rajouté typename dans
    forward_list<Entry>::iterator it;
    */
};}