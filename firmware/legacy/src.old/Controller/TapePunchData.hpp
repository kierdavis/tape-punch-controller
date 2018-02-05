namespace Controller {
  namespace TapePunchData {
    class PullByteResult {
    public:
      bool hasData;
      uint8_t data;
    };

    PullByteResult pullByte();
  }
}

// Use a linked list for the queue! Ring buffers are too much faff!
