sem_init(&full_slots, ..., 0);
sem_init(&empty_slots, ..., BUFFER_CAPACITY);
sem_init(&mutex, ..., 1 /* # thread that can use buffer at once */);
buffer.set_size(BUFFER_CAPACITY);
...
Produce(item) {
    sem_wait(&empty_slots);
    sem_wait(&mutex);
    buffer.enqueue(item);
    sem_post(&mutex);
    // tell consumers there is more data
    sem_post(&full_slots); 
}

Consume() {
    // wait until queued item, reserve it
    sem_wait(&full_slots); 
    sem_wait(&mutex);
    item = buffer.dequeue();
    sem_post(&mutex);
    // let producer reuse item slot
    sem_post(&empty_slots); 
    return item;
}
