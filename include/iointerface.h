/* Interface that should be implemented by IO classes */
#ifndef iointerface_h
#define iointerface_h
class IoInterface
{
  public:
    virtual void cmd(const uint8_t cmd) = 0;
    virtual void data(uint8_t data) = 0;
    virtual void data(const uint8_t *data, int len) = 0;
    virtual void reset(uint8_t millis) = 0;
    virtual void init(uint8_t frequency,bool debug) = 0;
};
#endif
