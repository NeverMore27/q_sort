#include <future>
#include <lomuto_partition.hpp>
#include <thread_safe_stack.hpp>
#include <thread>
#include <vector>

    template <typename BidirectionalIterator>
    class parallel_quick_sorter_t
    {
    private:
        struct chunk_to_sort_t
        {
            BidirectionalIterator first;
            BidirectionalIterator last;
            std::promise<void> promise;
        };
    public:
        parallel_quick_sorter_t();
        parallel_quick_sorter_t( parallel_quick_sorter_t const & other ) = delete;
        auto operator =( parallel_quick_sorter_t const & other ) -> parallel_quick_sorter_t & = delete;
        parallel_quick_sorter_t( parallel_quick_sorter_t && other ) = delete;
        auto operator =( parallel_quick_sorter_t && other ) -> parallel_quick_sorter_t & = delete;
        ~parallel_quick_sorter_t();

        void do_sort( BidirectionalIterator first, BidirectionalIterator last );
        void sort_thread();
        void try_sort_chunk();
        void sort_chunk( std::shared_ptr<chunk_to_sort_t> chunk );
    private:
        std::vector<std::thread> threads_;
        unsigned int const max_threads_count_;
        stack<chunk_to_sort_t> chunks_;
        std::atomic<bool> end_of_data_;
    };

    template <typename BidirectionalIterator>
    parallel_quick_sorter_t<BidirectionalIterator>::parallel_quick_sorter_t() :
    max_threads_count_{ std::thread::hardware_concurrency() - 1 },
        end_of_data_{ false }
    {
    }

    template <typename BidirectionalIterator>
    parallel_quick_sorter_t<BidirectionalIterator>::
    ~parallel_quick_sorter_t()
    {
        // устанавливает флаг об окочании данных
        // ожидает завершения потоков из пула
    }

    template <typename BidirectionalIterator>
    void
    parallel_quick_sorter_t<BidirectionalIterator>::
    do_sort( BidirectionalIterator first, BidirectionalIterator last )
    {
        if( first == last ) {
            return;
        }
        
        // разбивает на порцию данных на две
        // первую часть закидывает в стек задач
        // вторую часть сортирует сам
        
        // в цикле проверяет отсортировалась ли первая часть
        // если нет, то берет порцию данных из стека задач, и сортирует её
    }

    template <typename BidirectionalIterator>
    void
    parallel_quick_sorter_t<BidirectionalIterator>::
    try_sort_chunk()
    {
        // сортирует порцию данных, если она есть
    }

    template <typename BidirectionalIterator>
    void
    parallel_quick_sorter_t<BidirectionalIterator>::
    sort_thread()
    {
        // в цикле берет порцию данных из стека задач, и сортирует её
        // при этом на каждой итерации возвращает управление системе
        // чтобы та могла дать возможность поработать другим потокам
    }

    template <typename BidirectionalIterator>
    void parallel_quick_sorter_t<BidirectionalIterator>::sort_chunk( std::shared_ptr<chunk_to_sort_t> chunk )
    {

    }

    template <typename BidirectionalIterator>
    void parallel_quick_sort( BidirectionalIterator first, BidirectionalIterator last )
    {
        if( first == last ) {
            return;
        }

        parallel_quick_sorter_t<BidirectionalIterator> sorter;

        sorter.do_sort( first, last );
    }

