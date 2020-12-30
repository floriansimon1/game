#include <game/rendering/managed-opengl-resource.hpp>

namespace game::rendering {
    ManagedOpenglBuffer::ManagedOpenglBuffer(
        const Deleter& deleter,
        const GLuint   descriptor
    )
    : descriptor(descriptor)
    , deleter(deleter)
    {}

    ManagedOpenglBuffer::ManagedOpenglBuffer(
        ManagedOpenglBuffer&& buffer
    )
    : descriptor(std::move(buffer.descriptor))
    , deleter(std::move(deleter))
    {
        buffer.descriptor.reset();
    }

    ManagedOpenglBuffer::~ManagedOpenglBuffer() {
        if (this->descriptor.has_value()) {
            this->deleter(1, &this->descriptor.value());
        }
    }

    GLuint
    ManagedOpenglBuffer::unwrap() const {
        return this->descriptor.value();
    }

    ManagedOpenglBuffer
    ManagedOpenglBuffer::createVertexArray() {
        GLuint descriptor;

        glGenVertexArrays(1, &descriptor);

        return ManagedOpenglBuffer(glDeleteVertexArrays, descriptor);
    }

    ManagedOpenglBuffer
    ManagedOpenglBuffer::createGenericBuffer() {
        GLuint descriptor;

        glGenBuffers(1, &descriptor);

        return ManagedOpenglBuffer(glDeleteBuffers, descriptor);
    }
}
