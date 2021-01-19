template<typename T>
class Stack {
    public:
        virtual ~Stack() {}
        virtual void push(const T &t) = 0;
        virtual T pop() = 0;
        virtual T peek() const = 0;
        virtual bool isEmpty() const = 0;
};
