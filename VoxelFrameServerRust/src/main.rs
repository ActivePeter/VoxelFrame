mod net;
fn main() {
    // println!("Hello, world!");
    let server = net::Server::new();
    server.start();
}
