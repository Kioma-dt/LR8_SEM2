#include <vector>
#include <forward_list>

template <typename T>
class HashFunc{
    public:
    size_t hash(T key) const;
};

template<>
class HashFunc<int>{
    public:
    size_t hash(int key) const{
        size_t prime = 2654435761;
        return static_cast<size_t>(key) * prime;
    }
};

template <typename Key, typename Value, typename Func = HashFunc<Key>>
class HashTable {
   private:
    const size_t default_capacity_ = 16;
    size_t capacity_;
    size_t size_;
    std::vector<std::forward_list<std::pair<Key, Value>>> table_;
    Func hashfunc;
    size_t hashKey(const Key &key) const { return hashfunc.hash(key) % capacity_; }

    void reHash(size_t new_capcity) {
        std::vector<std::forward_list<std::pair<Key, Value>>> new_table(new_capcity);

        for (size_t i = 0; i < table_.size(); i++) {
            while (!table_[i].empty()) {
                auto temp_pair = table_[i].front();
                table_[i].pop_front();

                size_t new_hash = hashKey(temp_pair.first) % new_capcity;
                new_table[new_hash].push_front(temp_pair);
            }
        }

        table_ = std::move(new_table);
        capacity_ = new_capcity;
    }

   public:
    HashTable(size_t capacity  = 16)
        : capacity_(capacity), size_(0), table_(capacity_) {}

    void insert(const Key& key, const Value& value) {
        size_t index = hashKey(key);

        bool updated = false;

        for (auto pair = table_[index].begin(); pair!=table_[index].end(); pair++) {
            if(pair->first == key){
                pair->second = value;
                updated = true;
            }
        }

        if (!updated) {
            size_++;
            if (size_ > 0.75 * capacity_) {
                reHash(capacity_ * 2);
            }
            table_[index].push_front(make_pair(key, value));
        }
    }

    Value value(const Key& key) const {
        size_t index = hashKey(key);

        for (auto pair = table_[index].begin(); pair!=table_[index].end(); pair++) {
            if(pair->first == key){
                return pair->second;
            }
        }

        throw std::exception();
    }

    Value& operator[](const Key& key){
        size_t index = hashKey(key);

        if (!contains(key)){
            insert(key, Value());
        }

        Value* val;
        for (auto pair = table_[index].begin(); pair != table_[index].end(); pair++){
            if(pair->first == key){
                val = &pair->second;
            }
        }
        return *val;
    }

    const Value& operator[](const Key& key) const{
        size_t index = hashKey(key);

        if (!contains(key)){
            throw std::exception();
        }

        Value* val;
        for (auto pair = table_[index].begin(); pair != table_[index].end(); pair++){
            if(pair->first == key){
                val = &pair->second;
            }
        }
        return *val;
    }

    void remove(const Key& key) {
        size_t index = hashKey(key);

        auto prev = table_[index].before_begin();
        for (auto pair = table_[index].begin(); pair != table_[index].end(); pair++){
            if(pair->first == key){
                if(pair == table_[index].begin()){
                    table_[index].pop_front();
                    size_--;
                    return;
                }
                else{
                    table_[index].emplace_after(prev);
                    size_--;
                    return;
                }
            }
            prev++;
        }
    }

    bool contains(const Key& key) const {
        size_t index = hashKey(key);

        for (auto pair = table_[index].begin(); pair!=table_[index].end(); pair++) {
            if(pair->first == key){
                return true;
            }
        }

        return false;
    }

    size_t size() const { return size_; }

    size_t capacity() const { return capacity_; }

    bool empty() { return size_ == 0; }
};