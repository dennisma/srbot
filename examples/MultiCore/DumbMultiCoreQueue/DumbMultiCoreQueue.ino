
typedef struct
{
    char data;
} queue_entry_t;

queue_t call_queue;

void setup() {
  queue_init(&call_queue, sizeof(queue_entry_t), 20);
  Serial.begin(115200);
  while(!Serial);  
}

void loop() {
  queue_entry_t entry;
  queue_remove_blocking(&call_queue, &entry);
  Serial.print(entry.data);
}

void setup1() {
  while(!Serial);
}

void loop1() {
  queue_entry_t entry ;
  if (Serial.available()){
    char c = Serial.read();
    entry.data = c;
    queue_add_blocking(&call_queue, &entry);
  }
}
