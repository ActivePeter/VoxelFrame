pub struct Server {}

impl Server {
    pub fn new() -> Server {
        Server {}
    }
    pub fn start(&self) {
        println!("server start");
    }
    // pub fn public_method(&self) {
    //     println!("from public method");
    //     self.private_method();
    // }

    // fn private_method(&self) {
    //     println!("from private method");
    // }
}
