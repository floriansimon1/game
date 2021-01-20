#pragma once

#include <game/base/non-copyable.hpp>

#include <glad/glad.h>

#include <optional>
#include <functional>

namespace game::rendering {
    class ManagedOpenglBuffer: private game::base::NonCopyable {
        public:
            using Deleter = std::function<void(GLsizei number, const GLuint* buffers)>;

            ManagedOpenglBuffer(
                const Deleter&  deleter,
                const GLuint    descriptor
            );

            ManagedOpenglBuffer(
                ManagedOpenglBuffer&& buffer
            );

            ~ManagedOpenglBuffer();

            static ManagedOpenglBuffer
            createVertexArray();

            static ManagedOpenglBuffer
            createGenericBuffer();

            GLuint unwrap() const;

        private:
            std::optional<GLuint> descriptor;
            Deleter               deleter;
    };
}
