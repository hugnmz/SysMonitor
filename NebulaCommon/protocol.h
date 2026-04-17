#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QtGlobal>

namespace Nebula {

    // nhận diện người nhận
    const quint32 MAGIC_NUMBER = 0x4E424C41; // "NBLA"


        // Dùng quint16 để đảm bảo nó luôn chiếm 2 byte trên mọi hệ điều hành
        enum PacketType : quint16 {
            Auth_Challenge = 0x01,
            Auth_Response  = 0x02,
            Auth_Success   = 0x03,
            Auth_Failed    = 0x04,

            Get_Sys_Stats  = 0x10,
            Sys_Stats_Reply = 0x11,

            File_Header    = 0x20,
            File_Chunk     = 0x21,
            File_Finish    = 0x22
        };

    // cấu trúc tổng của Header (16bytes)
    #pragma pack(push, 1) // Ép kiểu dữ liệu không có khoảng trống (padding)
    struct Header {
        quint32 magic;       // 4 bytes
        quint16 version;     // 2 bytes
        quint16 type;        // 2 bytes (ép kiểu từ PacketType)
        quint64 payloadSize; // 8 bytes
    };
    #pragma pack(pop)
}

#endif // PROTOCOL_H
