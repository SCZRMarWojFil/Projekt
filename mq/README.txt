posix_producer musi miec uprawnienia, żeby zwiększyć limit pamięci w mq.
komenda:
    sudo setcap 'CAP_SYS_RESOURCE=+ep' bin/producer 
