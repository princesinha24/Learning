package builder_design_pattern;

public class User {
    private final String name;      // required
    private final int age;          // optional
    private final String email;     // optional
    private final String address;   // optional

    private User(Builder builder) {
        this.name = builder.name;
        this.age = builder.age;
        this.email = builder.email;
        this.address = builder.address;
    }

    public static class Builder {
        private final String name;  // required
        private int age;            // optional default 0
        private String email;
        private String address;

        public Builder(String name) {
            this.name = name;
        }

        public Builder age(int age) {
            this.age = age;
            return this;
        }

        public Builder email(String email) {
            this.email = email;
            return this;
        }

        public Builder address(String address) {
            this.address = address;
            return this;
        }

        public User build() {
            if (name == null || name.isBlank()) {
                throw new IllegalArgumentException("name is required");
            }
            return new User(this);
        }
    }
}

public class student {
    public static void main(String[] args) {
        User u = new User.Builder("Princsin")
        .age(25)
        .email("p@example.com")
        .build();
    }
}
