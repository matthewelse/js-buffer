/* Copyright (c) 2016 Matthew Else. All rights reserved.
 *
 * The MIT License (MIT)
 * Copyright (c) 2016 Matthew Else
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "jerryscript-mbed-util/logging.h"
#include "jerryscript-mbed-library-registry/wrap_tools.h"

#include "mbed.h"

typedef struct {
    uint8_t* buffer;
    size_t length;
} buffer_t;

DECLARE_CLASS_FUNCTION(Buffer, getUint8) {
    CHECK_ARGUMENT_COUNT(Buffer, getUint8, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(Buffer, getUint8, 0, number); // offset

    uintptr_t native_ptr;
    jerry_get_object_native_handle(this_obj, &native_ptr);

    buffer_t* buf = (buffer_t*)native_ptr;

    size_t offset = jerry_get_number_value(args[0]);

    if (offset < buf->length) {
        return jerry_create_number(buf->buffer[offset]);
    } else {
        return jerry_create_undefined();
    }
}

DECLARE_CLASS_FUNCTION(Buffer, getUint16) {
    CHECK_ARGUMENT_COUNT(Buffer, getUint16, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(Buffer, getUint16, 0, number); // offset (bytes)

    uintptr_t native_ptr;
    jerry_get_object_native_handle(this_obj, &native_ptr);

    buffer_t* buf = (buffer_t*)native_ptr;

    size_t offset = jerry_get_number_value(args[0]);

    if (offset + (sizeof(uint16_t) - 1) < buf->length) {
        uint16_t *u16buf = (uint16_t*)(buf->buffer + offset);
        return jerry_create_number(*u16buf);
    } else {
        return jerry_create_undefined();
    }
}

DECLARE_CLASS_FUNCTION(Buffer, getUint32) {
    CHECK_ARGUMENT_COUNT(Buffer, getUint32, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(Buffer, getUint32, 0, number); // offset (bytes)

    uintptr_t native_ptr;
    jerry_get_object_native_handle(this_obj, &native_ptr);

    buffer_t* buf = (buffer_t*)native_ptr;

    size_t offset = jerry_get_number_value(args[0]);

    if (offset + (sizeof(uint32_t) - 1) < buf->length) {
        uint32_t *u32buf = (uint32_t*)(buf->buffer + offset);
        return jerry_create_number(*u32buf);
    } else {
        return jerry_create_undefined();
    }
}

DECLARE_CLASS_FUNCTION(Buffer, getFloat32) {
    CHECK_ARGUMENT_COUNT(Buffer, getFloat32, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(Buffer, getFloat32, 0, number); // offset (bytes)

    uintptr_t native_ptr;
    jerry_get_object_native_handle(this_obj, &native_ptr);

    buffer_t* buf = (buffer_t*)native_ptr;

    size_t offset = jerry_get_number_value(args[0]);

    if (offset + (sizeof(float) - 1) < buf->length) {
        float *floatbuf = (float*)(buf->buffer + offset);
        return jerry_create_number(*floatbuf);
    } else {
        return jerry_create_undefined();
    }
}

DECLARE_CLASS_FUNCTION(Buffer, getFloat64) {
    CHECK_ARGUMENT_COUNT(Buffer, getFloat64, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(Buffer, getFloat64, 0, number); // offset (bytes)

    uintptr_t native_ptr;
    jerry_get_object_native_handle(this_obj, &native_ptr);

    buffer_t* buf = (buffer_t*)native_ptr;

    size_t offset = jerry_get_number_value(args[0]);

    if (offset + (sizeof(double) - 1) < buf->length) {
        double *floatbuf = (double*)(buf->buffer + offset);
        return jerry_create_number(*floatbuf);
    } else {
        return jerry_create_undefined();
    }
}

DECLARE_CLASS_FUNCTION(Buffer, setUint8) {
    CHECK_ARGUMENT_COUNT(Buffer, setUint8, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(Buffer, setUint8, 0, number); // offset
    CHECK_ARGUMENT_TYPE_ALWAYS(Buffer, setUint8, 1, number); // value

    uintptr_t native_ptr;
    jerry_get_object_native_handle(this_obj, &native_ptr);

    buffer_t* buf = (buffer_t*)native_ptr;

    size_t offset = jerry_get_number_value(args[0]);
    uint8_t data = jerry_get_number_value(args[1]);

    if (offset < buf->length) {
        buf->buffer[offset] = data;
    }

    return jerry_create_undefined();
}

DECLARE_CLASS_FUNCTION(Buffer, setUint16) {
    CHECK_ARGUMENT_COUNT(Buffer, setUint16, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(Buffer, setUint16, 0, number); // offset (bytes)
    CHECK_ARGUMENT_TYPE_ALWAYS(Buffer, setUint16, 1, number); // value

    uintptr_t native_ptr;
    jerry_get_object_native_handle(this_obj, &native_ptr);

    buffer_t* buf = (buffer_t*)native_ptr;

    size_t offset = jerry_get_number_value(args[0]);
    uint16_t value = jerry_get_number_value(args[1]);

    if (offset + (sizeof(uint16_t) - 1) < buf->length) {
        uint16_t *u16buf = (uint16_t*)(buf->buffer + offset);
        *u16buf = value;
    }

    return jerry_create_undefined();
}

DECLARE_CLASS_FUNCTION(Buffer, setUint32) {
    CHECK_ARGUMENT_COUNT(Buffer, setUint32, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(Buffer, setUint32, 0, number); // offset (bytes)
    CHECK_ARGUMENT_TYPE_ALWAYS(Buffer, setUint32, 1, number); // value


    uintptr_t native_ptr;
    jerry_get_object_native_handle(this_obj, &native_ptr);

    buffer_t* buf = (buffer_t*)native_ptr;

    size_t offset = jerry_get_number_value(args[0]);
    uint32_t value = jerry_get_number_value(args[1]);

    if (offset + (sizeof(uint32_t) - 1) < buf->length) {
        uint32_t *u32buf = (uint32_t*)(buf->buffer + offset);
        *u32buf = value;
    }

    return jerry_create_undefined();
}

DECLARE_CLASS_FUNCTION(Buffer, setFloat32) {
    CHECK_ARGUMENT_COUNT(Buffer, setFloat32, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(Buffer, setFloat32, 0, number); // offset (bytes)
    CHECK_ARGUMENT_TYPE_ALWAYS(Buffer, setFloat32, 1, number); // value

    uintptr_t native_ptr;
    jerry_get_object_native_handle(this_obj, &native_ptr);

    buffer_t* buf = (buffer_t*)native_ptr;

    size_t offset = jerry_get_number_value(args[0]);
    float value = jerry_get_number_value(args[1]);

    if (offset + (sizeof(float) - 1) < buf->length) {
        float *floatbuf = (float*)(buf->buffer + offset);
        *floatbuf = value;
    }

    return jerry_create_undefined();
}

DECLARE_CLASS_FUNCTION(Buffer, setFloat64) {
    CHECK_ARGUMENT_COUNT(Buffer, setFloat64, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(Buffer, setFloat64, 0, number); // offset (bytes)
    CHECK_ARGUMENT_TYPE_ALWAYS(Buffer, setFloat64, 1, number); // value

    uintptr_t native_ptr;
    jerry_get_object_native_handle(this_obj, &native_ptr);

    buffer_t* buf = (buffer_t*)native_ptr;

    size_t offset = jerry_get_number_value(args[0]);
    double value = jerry_get_number_value(args[1]);

    if (offset + (sizeof(double) - 1) < buf->length) {
        double *floatbuf = (double*)(buf->buffer + offset);
        *floatbuf = value;
    }

    return jerry_create_undefined();
}

DECLARE_CLASS_FUNCTION(Buffer, toUint8Array) {
    CHECK_ARGUMENT_COUNT(Buffer, toUint8Array, (args_count == 0));

    uintptr_t native_ptr;
    jerry_get_object_native_handle(this_obj, &native_ptr);

    buffer_t* buf = (buffer_t*)native_ptr;
    jerry_value_t array = jerry_create_array(buf->length);

    for (size_t i = 0; i < buf.length; i++) {
        jerry_set_property_by_index(array, jerry_create_number_value(buf.buffer[i]));
    }

    return array;
}

void NAME_FOR_CLASS_NATIVE_DESTRUCTOR(Buffer) (uintptr_t handle) {
    delete[] (buffer_t*)handle->buffer;
    delete (buffer_t*)handle;
}

/**
 * Constructor for Buffer class. Represents a raw buffer of bytes.
 *
 * @param length in bytes
 */
DECLARE_CLASS_CONSTRUCTOR(Buffer) {
    CHECK_ARGUMENT_COUNT(Buffer, __constructor, (args_count == 1));
    CHECK_ARGUMENT_TYPE_ALWAYS(Buffer, __constructor, 0, number);

    size_t count = jerry_get_number_value(args[0]);
    buffer_t* buf = new buffer_t;
    buf.buffer = new uint8_t[count];
    buf.length = count;
    uintptr_t native_ptr = (uintptr_t)buf;

    jerry_value_t js_object = jerry_create_object();
    jerry_set_object_native_handle(js_object, native_ptr, NAME_FOR_CLASS_NATIVE_DESTRUCTOR(Buffer));

    ATTACH_CLASS_FUNCTION(js_object, Buffer, getUint8);
    ATTACH_CLASS_FUNCTION(js_object, Buffer, getUint16);
    ATTACH_CLASS_FUNCTION(js_object, Buffer, getUint32);
    ATTACH_CLASS_FUNCTION(js_object, Buffer, getFloat32);
    ATTACH_CLASS_FUNCTION(js_object, Buffer, getFloat64);

    ATTACH_CLASS_FUNCTION(js_object, Buffer, setUint8);
    ATTACH_CLASS_FUNCTION(js_object, Buffer, setUint16);
    ATTACH_CLASS_FUNCTION(js_object, Buffer, setUint32);
    ATTACH_CLASS_FUNCTION(js_object, Buffer, setFloat32);
    ATTACH_CLASS_FUNCTION(js_object, Buffer, setFloat64);

    ATTACH_CLASS_FUNCTION(js_object, Buffer, toUint8Array);

    return js_object;
}
