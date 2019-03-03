# Learning Q&A

## 2-27 Wednesday

最大线程数为4为什么openmp可以指定线程数为6

`#pragma omp parallel num_threads(8)
{
printf(“Hello, World!, ThreadId=%d\n”, omp_get_thread_num() );
} `

 

