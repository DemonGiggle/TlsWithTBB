TlsWithTBB
==========

Well, few days ago, I ran into trouble when mixing tls and tbb library. Finally, I successfully narrow down the issue and this project is created.

Platform
--------

Ubuntu 11.04
glibc 2.13
gcc 4.7.1
tbb41 20121003oss

Test Software
-------------
valgrind 3.8.1

How to try
----------
1. make
2. valgrind ./a.out

Result
------

```
==13972== Memcheck, a memory error detector
==13972== Copyright (C) 2002-2012, and GNU GPL'd, by Julian Seward et al.
==13972== Using Valgrind-3.8.1 and LibVEX; rerun with -h for copyright info
==13972== Command: ./a.out
==13972== 
==13972== Invalid read of size 4
==13972==    at 0x52A5160: rml::internal::safer_dereference(rml::internal::BackRefIdx const*) (frontend.cpp:2144)
==13972==    by 0x52A51B0: rml::internal::isLargeObject(void*) (frontend.cpp:2159)
==13972==    by 0x52A5D88: safer_scalable_free (frontend.cpp:2577)
==13972==    by 0x529E105: __TBB_internal_free (tbbmalloc.cpp:209)
==13972==    by 0x54CF158: free (proxy.cpp:96)
==13972==    by 0x4011C68: _dl_deallocate_tls (dl-tls.c:481)
==13972==    by 0x620ED78: __free_stacks (allocatestack.c:277)
==13972==    by 0x5FB09D1: __libc_freeres (in /lib/x86_64-linux-gnu/libc-2.13.so)
==13972==    by 0x4A2362C: _vgnU_freeres (vg_preloaded.c:62)
==13972==    by 0x5EAA911: exit (exit.c:93)
==13972==    by 0x5E8FF05: (below main) (libc-start.c:258)
==13972==  Address 0x7863478 is 8 bytes before a block of size 8 alloc'd
==13972==    at 0x4C276CA: memalign (vg_replace_malloc.c:727)
==13972==    by 0x401129F: tls_get_addr_tail (dl-tls.c:529)
==13972==    by 0x401208F: __tls_get_addr (dl-tls.c:767)
==13972==    by 0x7C639DD: ???
==13972==    by 0x620FD8B: start_thread (pthread_create.c:304)
==13972==    by 0x5F59FDC: clone (clone.S:112)
==13972== 
==13972== 
==13972== HEAP SUMMARY:
==13972==     in use at exit: 8 bytes in 1 blocks
==13972==   total heap usage: 3 allocs, 2 frees, 1,040 bytes allocated
==13972== 
==13972== LEAK SUMMARY:
==13972==    definitely lost: 0 bytes in 0 blocks
==13972==    indirectly lost: 0 bytes in 0 blocks
==13972==      possibly lost: 0 bytes in 0 blocks
==13972==    still reachable: 8 bytes in 1 blocks
==13972==         suppressed: 0 bytes in 0 blocks
==13972== Rerun with --leak-check=full to see details of leaked memory
==13972== 
==13972== For counts of detected and suppressed errors, rerun with: -v
==13972== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 2 from 2)
```