from paramiko import SSHClient, RSAKey, AutoAddPolicy
import time


if __name__ == '__main__':
    host = "127.0.0.1";
    p = 2222;
    usr = "root";
    k = RSAKey.from_private_key_file("resources/keys/root_id_rsa")
    ssh = SSHClient()
    ssh.set_missing_host_key_policy(AutoAddPolicy())
    ssh.connect(hostname = host, port = p, username = usr, pkey = k)

    ssh.exec_command("mkdir /tmp/fuzzer");

    sftp = ssh.open_sftp()
    sftp.put("fuzzer_ssh/fuzzer/fuzzer", "/tmp/fuzzer/fuzzer")
    sftp.put("resources/configs/device.conf", "/tmp/fuzzer/device.conf")

    commands = ["chmod +rwx /tmp/fuzzer/fuzzer", "/tmp/fuzzer/fuzzer"];
    for command in commands:
        print("Executing {}".format(command));
        _, stdout, stderr = ssh.exec_command(command);
        time.sleep(1)
        print(stdout.read());
        print("Errors");
        print(stderr.read());


    sftp.get("/tmp/fuzzer/bug_report.txt", "resources/bug_reports/bug_report.txt")
    sftp.close()

    ssh.close()


