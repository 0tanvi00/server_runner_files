import akka.actor.ActorSystem
import akka.http.scaladsl.Http
import akka.http.scaladsl.server.Directives._
import scala.sys.process._

object Server extends App {
  implicit val system = ActorSystem("my-system")
  implicit val executionContext = system.dispatcher

  def callPythonScript(): Unit = {
    val exitCode = Seq("python", "test.py").!
    println(s"Python script exited with code $exitCode")
  }

  val route =
    pathEndOrSingleSlash {
      get {
        callPythonScript()
        complete("Scala (Akka HTTP) server is running!\n")
      }
    }

  Http().newServerAt("localhost", 3000).bind(route)
}
