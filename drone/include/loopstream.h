#ifndef LOOPSTREAM_H
#define LOOPSTREAM_H


class LoopStream
{
public:
    LoopStream(int size);
    ~LoopStream();

    bool isAvailable();

    void write(float data);
    bool read(float *data);

    float*  mBuffer;
    int     mRead;
    int     mWrite;
    int     mSize;

private:

};



#endif // LOOPSTREAM_H
